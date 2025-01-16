#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

int main() {
    srand(time(0));

    const int windowWidth = 400;
    const int windowHeight = 533;
    int platformCount = 10;

    sf::RenderWindow app(sf::VideoMode(windowWidth, windowHeight), "Doodle Game with Score!");
    app.setFramerateLimit(60);

    sf::Texture t1, t2, t3, restartTexture, closeTexture;
    t1.loadFromFile("Images/background.png");
    t2.loadFromFile("Images/platform.png");
    t3.loadFromFile("Images/doodle.png");
    if (!restartTexture.loadFromFile("Images/restart.png") || !closeTexture.loadFromFile("Images/close.png")) {
        std::cerr << "Failed to load textures!" << std::endl;
        return -1;
    }

    sf::Sprite sBackground(t1), sPlat(t2), sPers(t3), restartSprite(restartTexture), closeSprite(closeTexture);
    restartSprite.setPosition(230, 300);
    restartSprite.setScale(0.1f, 0.1f);
    closeSprite.setPosition(140, 295);
    closeSprite.setScale(0.12f, 0.12f);

    point plat[platformCount];
    initializePlatforms(plat, platformCount, windowWidth, windowHeight, 100);

    int x = 100, y = 100, h = 200;
    float dy = 0;
    int score = 0;
    bool isGameOver = false;

    sf::Font font;
    if (!font.loadFromFile("Text/arial.ttf")) {
        return -1;
    }
    sf::Text textScore;
    textScore.setFont(font);
    textScore.setCharacterSize(24);
    textScore.setFillColor(sf::Color::Black);
    textScore.setPosition(10, 10);

    sf::Text textGameOver;
    textGameOver.setFont(font);
    textGameOver.setCharacterSize(48);
    textGameOver.setFillColor(sf::Color::Red);
    textGameOver.setString("GAME OVER !!");
    textGameOver.setPosition(70, 230);

    while (app.isOpen()) {
        sf::Event e;
        while (app.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                app.close();
        }

        if (!isGameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                x += 3;
                if (x + 50 > windowWidth)
                    x = windowWidth - 50;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                x -= 3;
                if (x < 0)
                    x = 0;
            }

            dy += 0.25;
            y += dy;

            if (y > windowHeight) {
                isGameOver = true;
            }

            if (y < h) {
                score += static_cast<int>(h - y);
                y = h;
                updatePlatforms(plat, platformCount, windowHeight, dy, windowWidth, y);
            }

            detectCollision(x, y, dy, plat, platformCount);

            stringstream ss;
            ss << "Score: " << score;
            textScore.setString(ss.str());

            sPers.setPosition(x, y);

            drawGame(app, sBackground, sPers, sPlat, plat, platformCount, textScore);
        }
        else {
            displayGameOver(app, sBackground, textGameOver, restartSprite, closeSprite);

            if (e.type == sf::Event::MouseButtonPressed) {
                if (restartSprite.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
                    restartGame(x, y, score, isGameOver, platformCount, plat, textScore);
                }
                if (closeSprite.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
                    app.close();
                }
            }
        }
    }

    return 0;
}