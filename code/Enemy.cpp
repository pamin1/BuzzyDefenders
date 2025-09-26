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

void ECE_Enemy::display(sf::RenderWindow &win)
{
  win.draw(*this);
}