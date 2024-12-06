#pragma once
#include "../Block/Block.h"
#include <iostream>
#include <raylib.h>

class Obstacle
{
public:
    Obstacle (Vector2 position);

    void draw();

    Vector2 position;

    std::vector<Block> blocks;

    static std::vector<std::vector<int>> grid;

private:
};
