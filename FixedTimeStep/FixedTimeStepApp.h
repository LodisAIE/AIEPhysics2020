#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
class FixedTimeStepApp : public aie::Application {
public:

	FixedTimeStepApp();
	virtual ~FixedTimeStepApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	PhysicsScene* physicsScene;
protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};