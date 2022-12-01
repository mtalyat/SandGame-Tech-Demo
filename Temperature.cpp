#include "Temperature.h"

float const celciusToKelvin(float const temp)
{
    return temp + K_FREEZING;
}

float const kelvinToCelcius(float const temp)
{
    return temp - K_FREEZING;
}
