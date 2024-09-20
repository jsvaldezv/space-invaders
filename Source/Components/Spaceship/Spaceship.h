#pragma once
#include <raylib.h>

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
    
private:
    
    Texture2D image;
    Vector2 position;
    
};
