#include "LaserBlast.h"

ECE_LaserBlast::ECE_LaserBlast(const sf::Vector2f &pos, sf::Vector2f size = sf::Vector2f(4, 16))
    : sf::RectangleShape(size)
{
  auto b = getLocalBounds(); // (0,0,w,h)
  setOrigin(b.width * 0.5f, b.height * 0.5f);
  setFillColor(sf::Color::Green);
  setPosition(pos.x + 40, pos.y + 90);
}