#pragma once
#include <glm/ext.hpp>
enum ShapeType
{
	PLANE,
	SPHERE,
	BOX
};
class PhysicsObject
{
protected:
	ShapeType m_shapeID;
	PhysicsObject() {};
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) =0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};
};