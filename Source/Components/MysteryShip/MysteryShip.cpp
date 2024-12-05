#include "MysteryShip.h"

MysteryShip::MysteryShip()
{
    alive = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture (image);
}

void MysteryShip::prepare()
{
    image = LoadTexture ("../../Assets/mystery.png");
}

void MysteryShip::draw()
{
    if (alive)
        DrawTextureV (image, position, WHITE);
}

void MysteryShip::update()
{
    if (alive)
    {
        position.x += speed;
        
        if (position.x > GetScreenWidth() - image.width || position.x < 0)
            alive = false;
    }
}

void MysteryShip::spawn()
{
    position.y = 90;
    int side = GetRandomValue (0, 1);
    
    if (side == 0)
    {
        position.x = 0;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }
    
    alive = true;
}
