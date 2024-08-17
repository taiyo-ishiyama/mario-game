#include "game.h"
#include "resources.h"
#include "map.h"
#include "mario.h"
#include "physics.h"
#include <filesystem>
#include <iostream>
#include <SFML/Audio.hpp>

Map map(1.0f);
Camera camera(20.0f);
Mario mario{};
std::vector<Object *> objects{};

sf::Music music{};
bool paused{};
sf::Image image{};
sf::Font font{};
sf::Text coinsText("Coins", font);
sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

void Restart()
{
  Physics::Init();

  mario = Mario();
  mario.position = map.CreateFromImage(image, objects);

  mario.isDead = false;
  paused = false;

  mario.Begin();
  for (auto &object : objects)
  {
    object->Begin();
  }

  music.play();
}

void Begin(sf::RenderWindow &window)
{
  for (auto &file : std::__fs::filesystem::directory_iterator("../image/"))
  {
    if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
    {
      Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
    }
  }
  for (auto &file : std::__fs::filesystem::directory_iterator("../sounds/"))
  {
    if (file.is_regular_file() && (file.path().extension() == ".ogg" || file.path().extension() == ".wav"))
    {
      Resources::sounds[file.path().filename().string()].loadFromFile(file.path().string());
    }
  }

  music.openFromFile("../sounds/music.ogg");
  music.setLoop(true);
  music.setVolume(50);

  font.loadFromFile("../font.ttf");
  coinsText.setFillColor(sf::Color::White);
  coinsText.setOutlineColor(sf::Color::Black);
  coinsText.setOutlineThickness(1.0f);
  coinsText.setScale(0.1f, 0.1f);

  backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
  backgroundShape.setOrigin(0.5f, 0.5f);

  Physics::Init();

  if (!image.loadFromFile("../image/map2.png"))
  {
    std::cerr << "Failed to load image 'map.png'. Check the file path and ensure the file exists." << std::endl;
    exit(-1);
  }
  else
  {
    std::cout << "Image 'map.png' loaded successfully." << std::endl;
  }
  Restart();
}

void Update(float deltaTime)
{
  if (mario.isDead && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    Restart();

  if (mario.isDead || paused)
    return;
  Physics::Update(deltaTime);
  mario.Update(deltaTime);
  camera.position = mario.position;

  for (auto &object : objects)
  {
    object->Update(deltaTime);
  }
}

void Render(Renderer &renderer)
{
  renderer.Draw(Resources::textures["sky.png"], mario.position, camera.GetViewSize());
  for (auto &object : objects)
  {
    object->Render(renderer);
  }

  map.Draw(renderer);
  mario.Draw(renderer);

  // Physics::DebugDraw(renderer);
}

void RenderUI(Renderer &renderer)
{
  coinsText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
  coinsText.setString("Coins: " + std::to_string(mario.GetCoins()));
  renderer.target.draw(coinsText);

  if (paused)
  {
    backgroundShape.setScale(camera.GetViewSize());
    renderer.target.draw(backgroundShape);
  }
}

void DeleteObject(Object *object)
{
  const auto &it = std::find(objects.begin(), objects.end(), object);
  if (it != objects.end())
  {
    delete *it;
    objects.erase(it);
  }
}