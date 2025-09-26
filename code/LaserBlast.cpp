/*
Author: Prachit Amin
Class: ECE4122 A
Last Date Modified: 09/26/2025

Description:
Implementation of LaserBlast object.
*/

#include "LaserBlast.h"

ECE_LaserBlast::ECE_LaserBlast(const sf::Vector2f &pos, sf::Color c, sf::Vector2f size)
    : sf::RectangleShape(size)
{
  auto b = getLocalBounds(); // (0,0,w,h)
  setOrigin(b.width * 0.5f, b.height * 0.5f);
  setFillColor(c);
  setPosition(pos.x + 40, pos.y + 90);
}