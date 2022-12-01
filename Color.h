#ifndef COLOR_H
#define COLOR_H

#include "Math.h"

//creates a color using the given r, g, b and a values
int createColor(unsigned char const r, unsigned char const g, unsigned char const b, unsigned char const a = 0xff);

//gets the red value from the given color (BGRA form)
unsigned char getColorR(int const color);
//gets the green value from the given color (BGRA form)
unsigned char getColorG(int const color);
//gets the blue value from the given color (BGRA form)
unsigned char getColorB(int const color);
//gets the alpha value from the given color (BGRA form)
unsigned char getColorA(int const color);

//lerps between two colors
int lerpColor(int const color1, int const color2, float const t);

#endif