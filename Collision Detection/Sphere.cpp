#include "Sphere.h"
#include <Gizmos.h>
Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color) : Rigidbody(SPHERE,position,velocity,0,mass)
{
	m_radius = radius;
	m_color = color;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 21, m_color);
}

bool Sphere::checkCollision(PhysicsObject* pOther)
{
	Sphere* otherSphere = dynamic_cast<Sphere*>(pOther);
	if (otherSphere)
	{
		float distance = glm::distance(m_position, otherSphere->m_position);
		if (distance <= otherSphere->m_radius + m_radius)
		{
			return true;
		}
	}
	return false;
}
