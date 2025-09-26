/*
Author: Prachit Amin
Class: ECE4122 A
Last Date Modified: 09/26/2025

Description:
Header file for Buzzy object. Controls the hit status of the object.
*/

#include <SFML/Graphics.hpp>

class ECE_Buzzy : public sf::Sprite
{
public:
  ECE_Buzzy(const sf::Texture &tex);
  void moveBuzzy(const sf::Event &e);
  void handleKeyPress(const sf::Event &e);

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