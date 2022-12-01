#include "Math.h"

int getDirection(const float x)
{
	if (x > 0.0f)
	{
		return 1;
	}
	else if (x < 0.0f)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

float clamp(const float value, const float min, const float max)
{
	return std::min(max, std::max(value, min));
}

int clamp(const int value, const int min, const int max)
{
	return std::min(max, std::max(value, min));
}

float round(const float value, const int digits)
{
	return std::round(value * pow(10.0f, digits)) / pow(10.0f, digits);
}

int floorToInt(const float value)
{
	return static_cast<int>(floor(value));
}

int ceilToInt(const float value)
{
	return static_cast<int>(ceil(value));
}

int roundToInt(const float value)
{
	return static_cast<int>(round(value));
}

float sign(const float value)
{
	if (value > 0.0f)
	{
		return 1.0f;
	}
	else if (value < 0.0f)
	{
		return -1.0f;
	}
	else {
		return 0.0f;
	}
}

int sign(const int value)
{
	if (value > 0)
	{
		return 1;
	}
	else if (value < 0)
	{
		return -1;
	}
	else {
		return 0;
	}
}

float lerp(const float value1, const float value2, const float t)
{
	return value1 + (value2 - value1) * clamp(t, 0.0f, 1.0f);
}

int lerp(const int value1, const int value2, const float t)
{
	return roundToInt(value1 + (value2 - value1) * clamp(t, 0.0f, 1.0f));
}
