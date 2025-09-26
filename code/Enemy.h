#include <SFML/Graphics.hpp>

class ECE_Enemy : public sf::Sprite
{
public:
  ECE_Enemy();
  ECE_Enemy(const sf::Texture &tex);
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