/*
Author: Prachit Amin
Class: ECE4122 A
Last Date Modified: 09/26/2025

Description:
Header file for Enemy object. Controls the hit status of the object.
*/

#include <SFML/Graphics.hpp>

class ECE_Enemy : public sf::Sprite
{
public:
  ECE_Enemy();
  ECE_Enemy(const sf::Texture &tex);
  
  void setStatus(bool s)
  {
    this->status = s;
  }
  bool getStatus() const
  {
    return status;
  }

private:
  bool status = false;
};