/*
Author: Prachit Amin
Class: ECE4122 A
Last Date Modified: 09/26/2025

Description:
Implementation for LaserBlast object.
*/

#include "LaserBlast.h"

/**
 * @brief Constructor to initialize Sprite with RectangleShape, Color, and Size.
 * @param pos const reference to the Position desired for the RectangleShape.
 * @param c const reference to the Color desired for the RectangleShape.
 * @param size const reference to the Size desired for the RectangleShape.
 */
ECE_LaserBlast::ECE_LaserBlast(const sf::Vector2f &pos, const sf::Color &c, const sf::Vector2f &size)
    : sf::RectangleShape(size)
{
  auto b = getLocalBounds(); // (0,0,w,h)
  setOrigin(b.width * 0.5f, b.height * 0.5f);
  setFillColor(c);
  setPosition(pos.x + 40, pos.y + 90);
}