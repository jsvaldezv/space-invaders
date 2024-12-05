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
    
    lastFireTime = 0;
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
    if (GetTime() - lastFireTime >= 0.35)
    {
        lasers.emplace_back (Laser(Vector2({ position.x + image.width/2 - 2, position.y }), -6));
        lastFireTime = GetTime();
    }
}

Rectangle Spaceship::getRect()
{
    return { position.x, position.y, (float) image.width, (float) image.height };
}
