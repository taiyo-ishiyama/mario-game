#pragma once
#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "object.h"
#include "camera.h"

extern Camera camera;
extern bool paused;

void Begin(sf::RenderWindow &window);
void Update(float deltaTime);
void Render(Renderer &renderer);
void RenderUI(Renderer &renderer);

void DeleteObject(Object* object);