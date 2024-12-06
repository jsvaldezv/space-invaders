#pragma once
#include <raylib.h>
#include <iostream>
#include "../Block/Block.h"

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

