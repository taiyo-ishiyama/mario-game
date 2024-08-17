#include "map.h"
#include "resources.h"
#include "physics.h"
#include "coin.h"
#include "enemy.h"
#include <iostream>
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

Map::Map(float cellSize) : cellSize(cellSize), grid()
{
}

void Map::CreateCheckKeyboard(size_t width, size_t height)
{
  grid = std::vector<std::vector<sf::Texture *>>(width, std::vector<sf::Texture *>(height, nullptr));

  bool last = false;

  for (auto &column : grid)
  {
    for (auto &cell : column)
    {
      last = !last;
      if (last)
        cell = &Resources::textures["brick1.png"];
    }
    if (width % 2 == 0)
      last = !last;
  }
}

sf::Vector2f Map::CreateFromImage(const sf::Image &image, std::vector<Object *> &objects)
{
  objects.clear();
  grid.clear();
  grid = std::vector<std::vector<sf::Texture *>>(image.getSize().x, std::vector<sf::Texture *>(image.getSize().y, nullptr));

  sf::Vector2f marioPosition{};
  for (size_t x = 0; x < grid.size(); x++)
  {
    for (size_t y = 0; y < grid[x].size(); y++)
    {
      sf::Color color = image.getPixel(x, y);
      Object *object = nullptr;
      if (color == sf::Color::Red)
      {
        marioPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
        continue;
      }
      else if (color == sf::Color::Black)
      {
        grid[x][y] = &Resources::textures["brick1.png"];
      }
      else if (color == sf::Color::Green)
      {
        grid[x][y] = &Resources::textures["rock.png"];
      }
      else if (color == sf::Color::Yellow)
      {
        object = new Coin();
      }
      else if (color == sf::Color::Blue)
      {
        object = new Enemy();
      }

      if (object)
      {
        object->position = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
        objects.push_back(object);
      }
      else if (grid[x][y])
      {
        b2BodyDef bodyDef{};
        bodyDef.position.Set(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
        b2Body *body = Physics::world->CreateBody(&bodyDef);
        b2PolygonShape shape{};
        shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);

        FixtureData *fixtureData = new FixtureData();
        fixtureData->type = FixtureDataType::MapTile;
        fixtureData->mapX = x;
        fixtureData->mapY = y;

        b2FixtureDef fixtureDef{};
        fixtureDef.userData.pointer = (uintptr_t)fixtureData;
        fixtureDef.density = 0.0f;
        fixtureDef.shape = &shape;
        body->CreateFixture(&fixtureDef);
      }
    }
  }
  return marioPosition;
}

void Map::Draw(Renderer &renderer)
{
  int x = 0;
  for (const auto &column : grid)
  {
    int y = 0;
    for (const auto &cell : column)
    {
      if (cell)
      {
        renderer.Draw(*cell, sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
      }
      y++;
    }
    x++;
  }
}