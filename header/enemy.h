#pragma once

#include "animation.h"
#include "object.h"
#include "physics.h"

class Enemy
	: public Object
{
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;

	void Die();
	bool IsDead();

private:
	Animation animation{};
	float movement = 5.0f;

	float destroyTimer = 0.0f;
	bool isDead = false;

	FixtureData fixtureData{};
	b2Body* body{};
};
