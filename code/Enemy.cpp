/*
Author: Prachit Amin
Class: ECE4122 A
Last Date Modified: 09/26/2025

Description:
Implementation file for Enemy object.
*/

#include "Enemy.h"

ECE_Enemy::ECE_Enemy(){};

ECE_Enemy::ECE_Enemy(const sf::Texture &tex)
    : sf::Sprite(tex)
{
  // scale down sprite
  float wScale = 80 / this->getLocalBounds().width;
  float hScale = 80 / this->getLocalBounds().height;
  this->setScale(wScale, hScale);
}