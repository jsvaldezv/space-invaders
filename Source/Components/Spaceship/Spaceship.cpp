#include "Spaceship.h"

Spaceship::Spaceship()
{
    image = LoadTexture ("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height;
}

Spaceship::~Spaceship()
{
    UnloadTexture (image);
}

void Spaceship::Draw()
{
    DrawTextureV (image, position, WHITE);
}

void Spaceship::MoveLeft()
{
    
}

void Spaceship::MoveRight()
{
    
}

void Spaceship::FireLaser()
{
    
}
