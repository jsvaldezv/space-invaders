#include "Alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien (int ty, Vector2 pos)
{
    type = ty;
    position = pos;
    
    if (alienImages[type -1].id == 0)
    {
        switch (type)
        {
            case 1:
                alienImages[0] = LoadTexture ("../../Assets/alien1.png");
                break;
                
            case 2:
                alienImages[1] = LoadTexture ("../../Assets/alien2.png");
                break;
                
            case 3:
                alienImages[2] = LoadTexture ("../../Assets/alien3.png");
                break;
                
            default:
                alienImages[0] = LoadTexture ("../../Assets/alien1.png");
                break;
        }
    }
}

void Alien::draw()
{
    DrawTextureV (alienImages[type - 1], position, WHITE);
}

void Alien::update (int direction)
{
    position.x += direction;
}

int Alien::getType()
{
    return type;
}

void Alien::unloadImages()
{
    for (int i = 0; i < 4; i++)
        UnloadTexture (alienImages[i]);
}
