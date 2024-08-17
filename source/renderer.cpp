#include "renderer.h"
#include <vector>

Renderer::Renderer(sf::RenderTarget &target) : target(target)
{

}

void Renderer::Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, float angle)
{
  sprite.setTexture(texture, true);
  sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
  sprite.setPosition(position);
  sprite.setRotation(angle);
  sprite.setScale(sf::Vector2f(size.x / texture.getSize().x, size.y / texture.getSize().y));
  target.draw(sprite);
}