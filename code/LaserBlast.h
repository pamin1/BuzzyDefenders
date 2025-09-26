/*
Author: Prachit Amin
Class: ECE4122 A
Last Date Modified: 09/26/2025

Description:
Header file for LaserBlasts object.
*/

#include <SFML/Graphics.hpp>

class ECE_LaserBlast : public sf::RectangleShape
{
public:
  ECE_LaserBlast();
  explicit ECE_LaserBlast(const sf::Vector2f &pos, sf::Color c, sf::Vector2f size = {4.f, 16.f});

private:
  sf::RectangleShape shape;
  sf::Vector2f vel{0.0f, 0.0f};
  bool alive = false;
};