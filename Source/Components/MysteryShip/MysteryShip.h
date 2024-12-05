#pragma once
#include <raylib.h>

class MysteryShip
{
public:
    
    MysteryShip();
    ~MysteryShip();
    
    void prepare();
    
    void draw();
    
    void update();
    
    void spawn();
    
    bool alive;
    
private:
    
    Vector2 position;
    Texture2D image;
    int speed;
};

