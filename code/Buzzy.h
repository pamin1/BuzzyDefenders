#include <SFML/Graphics.hpp>

class ECE_Buzzy : public sf::Sprite
{
public:
  ECE_Buzzy(const sf::Texture &tex);
  void moveBuzzy(const sf::Event &e);
  void handleKeyPress(const sf::Event &e);
  void display(sf::RenderWindow &win);
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