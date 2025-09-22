#include "Buzzy.h"
#include "Enemy.h"
#include "LaserBlast.h"

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <list>
#include <random>

enum gameState
{
  HOME,
  PLAYING,
  GAMEOVER,
  EXIT
};

// templated vector for tracking LaserBlast objects
template <typename T>
int firstFreeIndex(std::vector<T> &v)
{
  for (int i = 0; i < (int)v.size(); ++i)
    if (!v[i].isAlive())
      return i;
  v.emplace_back(); // grow if none free
  return (int)v.size() - 1;
}

int main()
{
  // create variable sized window for the game
  constexpr int winWidth = 800, winHeight = 640;
  constexpr int ROWS = 4, COLS = 8;
  sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Buzzy Defender");
  sf::Texture texHome;
  if (!texHome.loadFromFile("graphics/Start_Screen.png"))
    return EXIT_FAILURE;
  sf::Sprite home(texHome);

  // scale the home screen to fit the window
  float wScale = winWidth / home.getLocalBounds().width;
  float hScale = winHeight / home.getLocalBounds().height;
  home.setScale(wScale, hScale);

  // initialize Buzzy sprite
  sf::Texture texBuzzy;
  texBuzzy.loadFromFile("graphics/Buzzy_blue.png");
  ECE_Buzzy buzzy(texBuzzy);
  buzzy.setPosition(360, 0);

  // initialize array of ECE_Enemy objects
  sf::Texture dogTex;
  sf::Texture tigerTex;
  dogTex.loadFromFile("graphics/bulldog.png");
  tigerTex.loadFromFile("graphics/clemson_tigers.png");

  ECE_Enemy enemies[ROWS][COLS];
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      const sf::Texture &tex = (i % 2 == 0) ? dogTex : tigerTex;
      enemies[i][j] = ECE_Enemy(tex);
      enemies[i][j].setPosition(80.f + 80.f * j, 280.f + 90.f * i);
    }
  }

  float speed = 0.5f;
  int dir = -1;        // left -> -1,  right -> +1
  float stepUp = -4.f; // dist to move up

  // lambda function for moving all the enemy sprites
  auto moveFormation = [&](float dx, float dy)
  {
    for (int i = 0; i < ROWS; ++i)
      for (int j = 0; j < COLS; ++j)
        enemies[i][j].move(dx, dy);
  };

  // lambda for getting the minimum and maximum X position of all the enemy sprites
  auto formationBounds = [&]()
  {
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    for (int i = 0; i < ROWS; ++i)
    {
      for (int j = 0; j < COLS; ++j)
      {
        const auto b = enemies[i][j].getGlobalBounds();
        minX = std::min(minX, b.left);
        maxX = std::max(maxX, b.left + b.width);
      }
    }
    return std::pair<float, float>{minX, maxX};
  };

  std::list<ECE_LaserBlast> pBlast;
  std::list<ECE_LaserBlast> eBlast;

  auto moveLaserBlast = [&](float dy)
  {
    for (auto &b : pBlast)
    {
      b.move(0, dy);
    }
    for (auto b : eBlast)
    {
      b.move(0, -dy);
    }
  };

  gameState state = HOME;
  while (window.isOpen())
  {
    sf::Event event;
    switch (state)
    {
      case (HOME):
        sf::Event event;
        window.clear();
        window.draw(home);
        window.display();
        while (window.pollEvent(event))
        {
          switch (event.type)
          {
            case sf::Event::Closed:
              window.close();
              break;
            case sf::Event::KeyPressed:
              if (event.key.code == sf::Keyboard::Enter)
              {
                state = PLAYING;
              }
          }
        }
        break;
      case (PLAYING):
        ECE_LaserBlast *laser;
        window.clear(sf::Color(112, 146, 190));
        while (window.pollEvent(event))
        {
          switch (event.type)
          {
            case sf::Event::Closed:
              window.close();
              break;
            case sf::Event::KeyPressed:
              if (event.key.code == sf::Keyboard::Space)
              {
                // shoot a laser
                pBlast.emplace_back(ECE_LaserBlast(buzzy.getPosition(), {6.f, 20.f}));
                std::cout
                    << buzzy.getPosition().x << ", " << buzzy.getPosition().y << "\n";
              }
              buzzy.handleKeyPress(event);
          }
        }

        // choose random num for enemy blast
        std::mt19937 rng{std::random_device{}()};
        int rnX = rand() % ROWS;
        int rnY = rand() % COLS;
        // eBlast.emplace_back(ECE_LaserBlast(enemies[rnX][rnY].getPosition()));

        // horizontal move
        float dx = dir * speed;
        moveFormation(dx, 0.f);

        // get the bounds for the enemy movements
        auto [minX, maxX] = formationBounds();
        float L = 0.0;
        float R = window.getSize().x;
        if (minX < L || maxX > R)
        {
          moveFormation(-dx, stepUp); // revert horizontal, go up
          dir = -dir;                 // flip
        }

        for (int i = 0; i < ROWS; i++)
        {
          for (const auto &e : enemies[i])
          {
            window.draw(e);
          }
        }

        // vertical move for laser blasts
        moveLaserBlast(speed);
        for (auto &b : pBlast)
        {
          window.draw(b);
        }
        for (auto &b : eBlast)
        {
          window.draw(b);
        }
        window.draw(buzzy);
        window.display();
    }
  }
}