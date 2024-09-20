#pragma once
#include <raylib.h>

class Laser
{
public:
    
    Laser (Vector2 position, int speed);
    ~Laser() = default;
    
    void update();
    
    void draw();
    
    bool active;
    
private:
    
    Vector2 position;
    int speed;
    
};
