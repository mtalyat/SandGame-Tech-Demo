#pragma once

#include <iostream>
#include <stdlib.h>
#include <cstdbool>
#include <algorithm>

//seeds the RNG based on the given seed
void random_seed(unsigned int const seed);
//seeds the RNG based on the current second
void random_seed_time();
//gets a value within the range [min, max)
int random_range(int const min, int const max);
//gets a value within the range [0, max)
int random_range(int const max);
//gets a value within the range [min, max]
float random_range(float const min, float const max);
//returns -1 or 1
int random_sign();