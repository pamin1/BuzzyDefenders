#include <SFML/Graphics.hpp>

class ECE_Enemy : public sf::Sprite
{
  public:
    ECE_Enemy();
    explicit ECE_Enemy(const sf::Texture &tex);
};