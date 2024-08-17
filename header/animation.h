#pragma once

#include <SFML/Graphics.hpp>

struct AnimFrame
{
  AnimFrame(float time = 0.0f, sf::Texture texture = sf::Texture()) : time(time), texture(texture)
  {
  }

  float time;
  sf::Texture texture{};
};

class Animation
{
public:
  Animation()
  {
  }
  Animation(float length, std::vector<AnimFrame> frames);
  void Update(float deltaTime);

  sf::Texture GetTexture();

private:
  float time = 0.0f;
  float length;
  std::vector<AnimFrame> frames;
};