#pragma once

#include <cmath>
#include <algorithm>

int getDirection(const float x);

float clamp(const float value, const float min, const float max);
int clamp(const int value, const int min, const int max);

float round(const float value, const int digits);
int floorToInt(const float value);
int ceilToInt(const float value);
int roundToInt(const float value);

float sign(const float value);
int sign(const int value);

float lerp(const float value1, const float value2, const float t);
int lerp(const int value1, const int value2, const float t);