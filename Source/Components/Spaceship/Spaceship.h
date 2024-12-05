#pragma once
#include <raylib.h>
#include "../Laser/Laser.h"
#include <vector>

class Spaceship
{
public:
    
    Spaceship() = default;
    ~Spaceship();
    
    void prepare();
  
    void draw();
    
    void moveLeft();
    
    void moveRight();
    
    void fireLaser();
    
    Rectangle getRect();
    
    std::vector<Laser> lasers;
    
private:
    
    Texture2D image;
    Vector2 position;
    
    double lastFireTime;
    
};
