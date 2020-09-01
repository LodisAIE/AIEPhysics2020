#include "PhysicsScene.h"
#include "Rigidbody.h"
#include <iostream>
#include <list>
#include "Sphere.h"
#include "Plane.h"
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);
static fn collisionFunctions[] =
{
	PhysicsScene::planeToPlane, PhysicsScene::planeToSphere,
	PhysicsScene::sphereToPlane, PhysicsScene::sphereToSphere
};
PhysicsScene::PhysicsScene()
{
	m_timeStep = 0.01f;
	m_gravity = { 0,0 };
}

PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	std::vector<PhysicsObject*>::iterator iterator = m_actors.begin();
	for (iterator = m_actors.begin(); iterator < m_actors.end(); ++iterator)
	{
		if (*iterator == actor)
		{
			break;
		}
	}
	m_actors.erase(iterator);
}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << " : " << std::endl;
	}
}

void PhysicsScene::update(float dt)
{
	static std::list<PhysicsObject*> dirty;

	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	
	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
		/*for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{
				if (pActor == pOther)
				{
					continue;
				}
				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
				{
					continue;
				}
				Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
				if (pRigid->checkCollision(pOther))
				{
					pRigid->applyForceToActor(dynamic_cast<Rigidbody*>(pOther), pRigid->getVelocity()* pRigid->getMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}*/
		checkForCollision();
		dirty.clear();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}

}

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	//Check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->GetShapeID();
			int shapeID2 = object2->GetShapeID();

			//using functions pointers
			int functionID = (shapeID1 * SHAPECOUNT) + shapeID2;
			fn collisionFunctionPtr = collisionFunctions[functionID];
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::planeToPlane(PhysicsObject*, PhysicsObject*)
{
	return false;
}

bool PhysicsScene::planeToSphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	sphereToPlane(obj2, obj1);
	return false;
}

bool PhysicsScene::sphereToPlane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);
	//if we are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(
			sphere->getPosition(),
			plane->getNormal()) - plane->getDistance();
		// if we are behind plane then we flip the normal
		if (sphereToPlane < 0) {
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}
		float intersection = sphere->getRadius() - sphereToPlane;
		if (intersection > 0) {
			sphere->applyForce(collisionNormal *sphere->getMass());
			//set sphere velocity to zero here
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphereToSphere(PhysicsObject*obj1, PhysicsObject* obj2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
	//If the cast is successful then test for collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		if (distance <= sphere1->getRadius() + sphere2->getRadius())
		{
			sphere1->applyForceToActor(dynamic_cast<Rigidbody*>(sphere2), sphere1->getVelocity()* sphere1->getMass());
			return true;
		}
	}
	return false;
}
