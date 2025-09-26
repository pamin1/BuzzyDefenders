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
  // initialize game variables
  gameState state = HOME;                        // game state
  constexpr int winWidth = 800, winHeight = 640; // window dimensions
  constexpr int ROWS = 4, COLS = 8;              // num rows and cols of enemies
  float speed = 0.25f;                           // "move speed" of objects
  int dir = -1;                                  // left -> -1,  right -> +1
  float stepUp = -4.f;                           // dist to move up
  std::list<ECE_LaserBlast> pBlast;              // player laser blasts
  std::list<ECE_LaserBlast> eBlast;              // enemy laser blasts
  sf::Clock eFire;                               // clock to space enemy laser blasts
  float eFireDelay = 2.0f;                       // timer

  // create variable sized window for the game
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

  // initialize enemies into 2D array
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
                pBlast.emplace_back(ECE_LaserBlast(buzzy.getPosition()));
              }
              buzzy.handleKeyPress(event);
          }
        }

        // horizontal move first
        // get the bounds for the enemy movements
        float dx = dir * speed;
        float minX = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::lowest();
        for (int i = 0; i < ROWS; ++i)
        {
          for (int j = 0; j < COLS; ++j)
          {
            ECE_Enemy temp = enemies[i][j];
            for (auto &b : pBlast) {
                // each sprite has a designated width and x,y position
                // check if the bottom pixels overlap with the range of the sprite position
                
            }
            enemies[i][j].move(dx, 0.0f);

            // track if enemies hit border
            const auto b = enemies[i][j].getGlobalBounds();
            minX = std::min(minX, b.left);
            maxX = std::max(maxX, b.left + b.width);
          }
        }

        // revert and shift up if the enemies hit border
        float L = 0.0;
        float R = window.getSize().x;
        if (minX < L || maxX > R)
        {
          for (int i = 0; i < ROWS; ++i)
          {
            for (int j = 0; j < COLS; ++j)
            {
              enemies[i][j].move(-dx, stepUp);
            }
          }
          dir = -dir; // flip
        }

        // choose random num for enemy blast
        std::mt19937 rng{std::random_device{}()};
        int rnX = rand() % ROWS;
        int rnY = rand() % COLS;
        if (eFire.getElapsedTime().asSeconds() >= eFireDelay)
        {
          eBlast.emplace_back(ECE_LaserBlast(enemies[rnX][rnY].getPosition()));
          eFire.restart();
        }

        // draw enemies
        for (int i = 0; i < ROWS; i++)
        {
          for (const auto &e : enemies[i])
          {
            window.draw(e);
          }
        }

        // move and draw laser blasts
        for (auto &b : pBlast)
        {
          b.move(0, speed);
          window.draw(b);
        }

        for (auto &b : eBlast)
        {
          b.move(0, -speed);
          window.draw(b);
        }

        window.draw(buzzy);
        window.display();
    }
  }
}