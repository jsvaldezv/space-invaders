#pragma once
#include <raylib.h>
#include <vector>

namespace Colours
{
    static constexpr Color Grey = { 29, 29, 27, 255 };
    static constexpr Color Yellow = { 243, 216, 63, 255 };
}

namespace Fonts
{
    static Font font = LoadFontEx ("../../Assets/monogram.ttf", 64, 0, 0);
}
