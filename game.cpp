#include "game.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void adjustPlatformCount(int& count, int y, int maxPlatforms) {
    count = max(2, static_cast<int>(maxPlatforms * (1.0f - y / 800.0f)));
}

void initializePlatforms(point plat[], int count, int windowWidth, int windowHeight, int playerStartY) {
    plat[0].x = rand() % (windowWidth - 68);
    plat[0].y = playerStartY + 70;

    for (int i = 1; i < count; i++) {
        plat[i].x = rand() % (windowWidth - 68);
        plat[i].y = rand() % (windowHeight - 14);

        while ((plat[i].y > playerStartY + 50) && (plat[i].y < playerStartY + 90)) {
            plat[i].y = rand() % (windowHeight - 14);
        }
    }
}

void updatePlatforms(point plat[], int& count, int windowHeight, float dy, int windowWidth, int y) {
    adjustPlatformCount(count, y, 10);

    for (int i = 0; i < count; i++) {
        plat[i].y -= dy;
        if (plat[i].y > windowHeight) {
            plat[i].y = rand() % 200;
            plat[i].x = rand() % (windowWidth - 68);
        }
    }
}

bool detectCollision(int x, int y, float& dy, const point plat[], int count) {
    for (int i = 0; i < count; i++) {
        if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) &&
            (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)) {
            dy = -12;
            return true;
        }
    }
    return false;
}

void drawGame(sf::RenderWindow& app, sf::Sprite& background, sf::Sprite& doodle, 
              sf::Sprite& platform, const point plat[], int count, sf::Text& scoreText) {
    app.clear();
    app.draw(background);

    for (int i = 0; i < count; i++) {
        platform.setPosition(plat[i].x, plat[i].y);
        app.draw(platform);
    }

    app.draw(doodle);
    app.draw(scoreText);

    app.display();
}

void displayGameOver(sf::RenderWindow& app, sf::Sprite& background, sf::Text& gameOverText, sf::Sprite& restartSprite, sf::Sprite& closeSprite) {
    app.clear();
    app.draw(background);
    app.draw(gameOverText);

    app.draw(restartSprite);
    app.draw(closeSprite);
    app.display();
}

void restartGame(int& x, int& y, int& score, bool& isGameOver, int platformCount, point plat[], sf::Text& scoreText) {
    x = 100;
    y = 100;
    score = 0;
    isGameOver = false;
    initializePlatforms(plat, platformCount, 400, 533, y);
    scoreText.setString("Score: 0");
}