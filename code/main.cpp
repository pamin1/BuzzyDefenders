#include "Buzzy.h"
#include "Enemy.h"
#include "LaserBlast.h"

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

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
    int winWidth = 800, winHeight = 600;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Buzzy Defender");
    sf::Texture homeTexture;
    if (!homeTexture.loadFromFile("graphics/Start_Screen.png"))
        return EXIT_FAILURE;
    sf::Sprite home(homeTexture);

    // scale the home screen to fit the window
    float wScale = winWidth / home.getLocalBounds().width;
    float hScale = winHeight / home.getLocalBounds().height;
    home.setScale(wScale, hScale);

    sf::Texture tex;
    tex.loadFromFile("graphics/Buzzy_blue.png");
    ECE_Buzzy buzzy(tex);
    buzzy.setPosition(360, 0);

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
                window.display();
        }
    }
}