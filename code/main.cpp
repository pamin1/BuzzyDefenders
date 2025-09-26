/*
Author: Prachit Amin
Class: ECE4122 A
Last Date Modified: 09/26/2025

Description:
Main game logic for Buzzy Defenders game.
*/

#include "Buzzy.h"
#include "Enemy.h"
#include "LaserBlast.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

// simple state machine for game logic
enum gameState
{
  HOME,
  PLAYING
};

int main()
{
  // initialize game variables
  gameState state = HOME;                        // game state
  constexpr int winWidth = 800, winHeight = 640; // window dimensions
  constexpr int ROWS = 4, COLS = 8;              // num rows and cols of enemies
  float speed = 0.20f;                           // "move speed" of objects
  int dir = -1;                                  // left -> -1,  right -> +1
  float stepUp = -4.f;                           // dist to move up
  std::vector<ECE_LaserBlast> pBlast;            // player laser blasts
  std::vector<ECE_LaserBlast> eBlast;            // enemy laser blasts
  sf::Clock eFire;                               // clock to space enemy laser blasts
  float eFireDelay = 2.0f;                       // timer
  ECE_Enemy enemies[ROWS][COLS];                 // array for enemy objects
  int numTagged = 0;                             // count for how many target are hit

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

        // check for game start condition
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

        // reset/intialization for actively changing variables
        numTagged = 0;
        pBlast.clear();
        eBlast.clear();
        buzzy.setStatus(false);
        for (int i = 0; i < ROWS; ++i)
        {
          for (int j = 0; j < COLS; ++j)
          {
            const sf::Texture &tex = (i % 2 == 0) ? dogTex : tigerTex; // alternating lines of dawgs and tigers
            enemies[i][j] = ECE_Enemy(tex);
            enemies[i][j].setPosition(80.f + 80.f * j, 280.f + 90.f * i);
          }
        }
        break;
      case (PLAYING):
      {
        ECE_LaserBlast *laser;
        window.clear(sf::Color(112, 146, 190));

        // check for move or blast
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
                pBlast.push_back(ECE_LaserBlast(buzzy.getPosition(), sf::Color::Green));
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
            // check if any of the laser blasts intersected the enemy
            for (int k = 0; k < pBlast.size(); k++)
            {
              auto tempBounds = enemies[i][j].getGlobalBounds();
              auto laseBounds = pBlast.at(k).getGlobalBounds();

              // found intersection means that the laser and enemy collided
              if (!enemies[i][j].getStatus() && tempBounds.intersects(laseBounds))
              {
                enemies[i][j].setStatus(true); // indicate that the enemy is hit
                auto it = pBlast.begin();
                std::advance(it, k);
                pBlast.erase(it); // remove the blast so it is not misinterpreted later
                numTagged++;
              }
            }
            // temporary move
            enemies[i][j].move(dx, 0.0f);

            // track if enemies hit border
            const auto b = enemies[i][j].getGlobalBounds();
            if (!enemies[i][j].getStatus())
            {
              minX = std::min(minX, b.left);
              maxX = std::max(maxX, b.left + b.width);
            }
          }
        }

        // revert and shift up if the enemies hit border
        if (minX < 0.0 || maxX > winWidth)
        {
          for (int i = 0; i < ROWS; ++i)
          {
            for (int j = 0; j < COLS; ++j)
            {
              enemies[i][j].move(-dx, stepUp);
            }
          }
          dir = -dir; // flip directions in this case
        }

        // choose random index for enemy to shoot laser
        std::mt19937 rng{std::random_device{}()};
        int rnX = rand() % ROWS;
        int rnY = rand() % COLS;
        if (!enemies[rnX][rnY].getStatus() && eFire.getElapsedTime().asSeconds() >= eFireDelay)
        {
          eBlast.push_back(ECE_LaserBlast(enemies[rnX][rnY].getPosition(), sf::Color::Red));
          eFire.restart();
        }

        // draw enemies
        for (int i = 0; i < ROWS; i++)
        {
          for (const auto &e : enemies[i])
          {
            if (!e.getStatus())
            {
              window.draw(e);
            }
          }
        }

        // move and draw laser blasts
        for (auto &b : pBlast)
        {
          b.move(0, speed);
          window.draw(b);
        }

        // move, draw, and check if enemy laser hit buzzy
        for (int i = 0; i < eBlast.size(); i++)
        {
          auto &b = eBlast.at(i);
          auto tempBounds = buzzy.getGlobalBounds();
          auto laseBounds = b.getGlobalBounds();
          if (tempBounds.intersects(laseBounds))
          {
            // lose condition
            buzzy.setStatus(true);
            std::cout << "You lost, game over\n";
            state = HOME;
          }

          b.move(0, -speed);
          window.draw(b);
        }

        // win condition
        if (numTagged == ROWS * COLS)
        {
          std::cout << "You won, game over\n";
          state = HOME;
        }

        window.draw(buzzy);
        window.display();

        break;
      }
    }
  }
}