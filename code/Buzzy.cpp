/*
Author: Prachit Amin
Class: ECE4122 A
Last Date Modified: 09/26/2025

Description:
Implementation file for Buzzy object.
*/

#include "Buzzy.h"

/**
 * @brief Constructor to initialize Sprite with Texture.
 * @param tex const reference to the Texture populating Sprite parent class.
 */
ECE_Buzzy::ECE_Buzzy(const sf::Texture &tex)
    : sf::Sprite(tex)
{
  // scale down sprite
  float wScale = 80 / this->getLocalBounds().width;
  float hScale = 80 / this->getLocalBounds().height;
  this->setScale(wScale, hScale);
}

/**
 * @brief Handles left/right movement of Buzzy object.
 * @param e user input sf::Event object.
 */
void ECE_Buzzy::handleKeyPress(const sf::Event &e)
{
  // event handling and movement bounds
  if (e.key.code == sf::Keyboard::Left && this->getPosition().x > 0)
  {
    this->setPosition(this->getPosition().x - 10, this->getPosition().y);
  }
  else if (e.key.code == sf::Keyboard::Right && this->getPosition().x < 720)
  {
    this->setPosition(this->getPosition().x + 10, this->getPosition().y);
  }
}