#include "Plane.h"
#include <Gizmos.h>
#include <glm/ext.hpp>
Plane::Plane() : PhysicsObject(PLANE)
{
	m_normal = { 0,1 };
	m_distanceToOrigin = 0;
}

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(PLANE)
{
	m_normal = normal;
	m_distanceToOrigin = distance;
}

Plane::~Plane()
{
}



void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	//easy to rotate normal through 90 degrees on z
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 color(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, color);
}

void Plane::resolveCollision(Rigidbody* actor2, glm::vec2 contact)
{
	
	glm::vec2 relativeVelocity = actor2->getVelocity();
	
	float elasticity = actor2->getElasticity();
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), m_normal) /(1 / actor2->getMass());

	glm::vec2 force = m_normal * j;

	actor2->applyForce(force, contact - actor2->getPosition());
}
