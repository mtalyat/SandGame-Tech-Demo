#include "Random.h"

void random_seed(unsigned int const seed)
{
	srand(seed);
}

void random_seed_time()
{
	srand(time(0));
}

int random_range(int const min, int const max)
{
	if (min >= max)
	{
		return 0;
	}

	return min + (rand() % (max - min));
}

int random_range(int const max)
{
	return rand() % max;
}

float random_range(float const min, float const max)
{
	if (min >= max)
	{
		return 0;
	}

	return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}

int random_sign()
{
	return (rand() % 2) * 2 - 1;
}
