#pragma once
#include <raylib.h>

class Alien
{
public:
    Alien (int type, Vector2 position);

    int type;

    Vector2 position;

    void update (int direction);

    void draw();

    int getType();

    Rectangle getRect();

    static Texture2D alienImages[3];

    static void unloadImages();

private:
};
