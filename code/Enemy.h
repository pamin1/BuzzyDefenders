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
  ECE_Enemy(){};
  ECE_Enemy(const sf::Texture &tex);

  /**
   * @brief Changes hit status of the object.
   * @param s Boolean value to change the status to.
   */
  void setStatus(bool s)
  {
    this->status = s;
  }

  /**
   * @brief Returns the hit status of the object.
   * @return Returns boolean hit status value.
   */
  bool getStatus() const
  {
    return status;
  }

private:
  bool status = false;
};