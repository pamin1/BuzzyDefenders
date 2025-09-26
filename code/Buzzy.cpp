#include "Buzzy.h"
#include <iostream>

ECE_Buzzy::ECE_Buzzy(const sf::Texture &tex)
    : sf::Sprite(tex)
{
  // scale down sprite
  float wScale = 80 / this->getLocalBounds().width;
  float hScale = 80 / this->getLocalBounds().height;
  this->setScale(wScale, hScale);
}

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

void ECE_Buzzy::display(sf::RenderWindow &win)
{
  win.draw(*this);
}