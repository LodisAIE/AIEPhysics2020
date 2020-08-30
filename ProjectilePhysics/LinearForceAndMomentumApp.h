#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
class LinearForceAndMomentumApp : public aie::Application {
public:

	LinearForceAndMomentumApp();
	virtual ~LinearForceAndMomentumApp();

	virtual bool startup();
	virtual void shutdown();
	void setupContinuousDemo(glm::vec2 startPos, glm::vec2 velocity, float gravity);
	virtual void update(float deltaTime);
	virtual void draw();
	PhysicsScene* physicsScene;
protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};