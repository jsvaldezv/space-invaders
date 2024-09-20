#include "Spaceship.h"

Spaceship::~Spaceship()
{
    UnloadTexture (image);
}

void Spaceship::prepare()
{
    image = LoadTexture ("../../Assets/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height;
}

void Spaceship::draw()
{
    DrawTextureV (image, position, WHITE);
}

void Spaceship::moveLeft()
{
    position.x -= 7;
    
    if (position.x < 0)
        position.x = 0;
}

void Spaceship::moveRight()
{
    position.x += 7;
    
    if (position.x > GetScreenWidth() - image.width)
        position.x = GetScreenWidth() - image.width;
}

void Spaceship::fireLaser()
{
    
}
