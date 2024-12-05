#pragma once
#include "../Helpers/Colours.h"
#include "../Helpers/Sizes.h"
#include "Obstacle/Obstacle.h"
#include "Spaceship/Spaceship.h"
#include "Alien/Alien.h"
#include <iostream>
#include <raylib.h>

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

private:
    
    void deleteInactiveLasers();
    
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
    
};
