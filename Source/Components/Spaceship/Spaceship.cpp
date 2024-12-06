#include "Spaceship.h"

Spaceship::~Spaceship()
{
    UnloadTexture (image);
}

void Spaceship::prepare()
{
    image = LoadTexture ("../../Assets/spaceship.png");

    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;

    lastFireTime = 0;
}

void Spaceship::draw()
{
    DrawTextureV (image, position, WHITE);
}

void Spaceship::moveLeft()
{
    position.x -= 7;

    if (position.x < 25)
        position.x = 25;
}

void Spaceship::moveRight()
{
    position.x += 7;

    if (position.x > GetScreenWidth() - image.width - 25)
        position.x = GetScreenWidth() - image.width - 25;
}

void Spaceship::fireLaser()
{
    if (GetTime() - lastFireTime >= 0.35)
    {
        lasers.emplace_back (Laser (Vector2 ({ position.x + image.width / 2 - 2, position.y }), -6));
        lastFireTime = GetTime();
    }
}

Rectangle Spaceship::getRect()
{
    return { position.x, position.y, (float) image.width, (float) image.height };
}

void Spaceship::reset()
{
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = (GetScreenHeight() - image.height) - 100;

    lasers.clear();
}
