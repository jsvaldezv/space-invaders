#include "Block.h"

Block::Block (Vector2 pos)
{
    position = pos;
}

void Block::draw()
{
    DrawRectangle (position.x, position.y, 3, 3, { 243, 216, 63, 255 });
}
