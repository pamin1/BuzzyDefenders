#include "Buzzy.h"
#include "Enemy.h"
#include "LaserBlast.h"

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

enum gameState
{
    HOME,
    PLAYING,
    GAMEOVER,
    EXIT
};

int main()
{
    // create variable sized window for the game
    int winWidth = 800, winHeight = 640;
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

    ECE_Enemy enemies[4][8];
    // enemies.reserve(10);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 8; j++)
        {
            const sf::Texture &tex = (i % 2 == 0) ? dogTex : tigerTex;
            ECE_Enemy e(tex); // ECE_Enemy should store/ref the texture
            e.setPosition(80 + 80.f * j, 280 + 90.f * i);
            enemies[i][j] = e;
        }
    }

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
                while (window.pollEvent(event))
                {
                    switch (event.type)
                    {
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case sf::Event::KeyPressed:
                            buzzy.handleKeyPress(event);
                    }
                }

                window.clear(sf::Color(112, 146, 190));
                window.draw(buzzy);
                for (int i = 0; i < 4; i++)
                {
                    for (const auto &e : enemies[i])
                    {
                        window.draw(e);
                    }
                }
                window.display();
        }
    }
}