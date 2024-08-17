#pragma once
#include "object.h"
#include "animation.h"
#include "physics.h"
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include <memory>

class Coin : public Object
{
public:
  ~Coin();
  virtual void Begin() override;
  virtual void Update(float deltaTime) override;
  virtual void Render(Renderer &renderer) override;

private:
  Animation animation;
  b2Body* body;
  std::unique_ptr<FixtureData> fixtureData;
};