#pragma once
#include "../Helpers/Assets.h"
#include "../Helpers/Sizes.h"
#include "Alien/Alien.h"
#include "MysteryShip/MysteryShip.h"
#include "Obstacle/Obstacle.h"
#include "Spaceship/Spaceship.h"
#include <iostream>
#include <raylib.h>
#include <string>

inline std::string FormatWithLeadingZeros (int number, int width)
{
    std::string numberText = std::to_string (number);
    int leadingZeros = (int) (width - numberText.length());
    return numberText = std::string (leadingZeros, '0') + numberText;
}

class MainComponent
{
public:
    explicit MainComponent();
    ~MainComponent();

    void prepare();

    void process();

    void draw();

    void drawBackground();

    void update();

    void handleInput();

    void checkForCollisions();

    bool run;

private:
    void deleteInactiveLasers();

    void gameOver();

    void reset();

    Spaceship spaceship;

    std::vector<Obstacle> createObstacles();
    std::vector<Obstacle> obstacles;

    std::vector<Alien> createAliens();
    std::vector<Alien> aliens;
    std::vector<Laser> alienLasers;

    void alienShootLaser();
    void moveAliens();
    void moveDownAliens (int distance);

    int aliensDirection;
    constexpr static float alienLaserShootInterval = 0.35f;
    float timeLastAlienFired;

    MysteryShip mysteryShip;
    float mysteryShipSpawnInterval;
    float timeLastSpawn;

    int lives;
    Texture2D SpaceshipImage;

    int score;
    int highScore;
    void checkForHighScore();
};
