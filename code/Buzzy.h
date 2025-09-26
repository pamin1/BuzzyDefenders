#include <SFML/Graphics.hpp>

class ECE_Buzzy : public sf::Sprite
{
public:
  ECE_Buzzy(const sf::Texture &tex);
  void moveBuzzy(const sf::Event &e);
  void handleKeyPress(const sf::Event &e);
  void display(sf::RenderWindow &win);
};