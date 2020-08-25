#include "Rigidbody.h"
#include <iostream>


Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
}

void Rigidbody::debug()
{
	std::cout << "Position: " << m_position.x << "," << m_position.y << std::endl;
	std::cout << "Velocity: " << m_velocity.x << "," << m_velocity.y << std::endl;
	std::cout << "Mass: " << m_mass << std::endl;

}

void Rigidbody::applyForce(glm::vec2 force)
{
	glm::vec2 newVec = (force / m_mass);
	m_velocity += newVec;
}

void Rigidbody::applyForceToActor(Rigidbody* otherActor, glm::vec2 force)
{
	otherActor->applyForce(force);
	applyForce(-force);
}
