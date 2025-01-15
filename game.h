#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct point {
    int x, y;
};

void adjustPlatformCount(int& count, int y, int maxPlatforms);
void initializePlatforms(point plat[], int count, int windowWidth, int windowHeight, int playerStartY);
void updatePlatforms(point plat[], int& count, int windowHeight, float dy, int windowWidth, int y);
bool detectCollision(int x, int y, float& dy, const point plat[], int count);
void drawGame(sf::RenderWindow& app, sf::Sprite& background, sf::Sprite& doodle,
              sf::Sprite& platform, const point plat[], int count, sf::Text& scoreText);
void displayGameOver(sf::RenderWindow& app, sf::Sprite& background, sf::Text& gameOverText, sf::Sprite& restartSprite, sf::Sprite& closeSprite);
void restartGame(int& x, int& y, int& score, bool& isGameOver, int platformCount, point plat[], sf::Text& scoreText);

#endif // GAME_H