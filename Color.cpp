#include "Color.h"

int createColor(unsigned char const r, unsigned char const g, unsigned char const b, unsigned char const a)
{
    return (b << 24) | (g << 16) | (r << 8) | a;
}

unsigned char getColorR(int const color)
{
    return (color >> 8) & 0x000000ff;
}

unsigned char getColorG(int const color)
{
    return (color >> 16) & 0x000000ff;
}

unsigned char getColorB(int const color)
{
    return (color >> 24) & 0x000000ff;
}

unsigned char getColorA(int const color)
{
    return color & 0x000000ff;
}

int lerpColor(int const color1, int const color2, float const t)
{
    return createColor(
        lerp(getColorR(color1), getColorR(color2), t),
        lerp(getColorG(color1), getColorG(color2), t),
        lerp(getColorB(color1), getColorB(color2), t),
        lerp(getColorA(color1), getColorA(color2), t)
    );
}
