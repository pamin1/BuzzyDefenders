#include <SFML/Graphics.hpp>

class ECE_Enemy : public sf::Sprite
{
public:
  ECE_Enemy();
  ECE_Enemy(const sf::Texture &tex);
  void display(sf::RenderWindow &win);
};