#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "renderer.h"
#include "object.h"

class Map
{
public:
  Map(float cellSize = 32.0f);
  void CreateCheckKeyboard(size_t width, size_t height);
  sf::Vector2f CreateFromImage(const sf::Image& image, std::vector<Object*>& objects);
  void Draw(Renderer& renderer);

  std::vector<std::vector<sf::Texture*>> grid;
  float cellSize;
};