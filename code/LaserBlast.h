#include <SFML/Graphics.hpp>

class ECE_LaserBlast : public sf::RectangleShape
{
public:
  ECE_LaserBlast();
  ECE_LaserBlast(const sf::Vector2f &pos, sf::Vector2f size);

private:
  sf::RectangleShape shape;
  sf::Vector2f vel{0.0f, 0.0f};
  bool alive = false;
};