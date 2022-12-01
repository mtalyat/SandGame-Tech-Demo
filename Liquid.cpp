#include "Liquid.h"

bool Liquid::onUpdate(Matrix::UpdateData const& data)
{
	static int leftCounts = 0;
	static int rightCounts = 0;

	int targetX = data.x + xVel;
	int targetY = data.y + yVel;

	data.matrix->findEmptyElement(data.x, data.y, targetX, targetY);

	if (data.x == targetX && data.y == targetY)
	{
		//did not move, try dispersing and moving again
		xVel = 0;
		yVel = 0;
		int dispersion = getDispersion();
		int direction = random_sign();

		targetX = data.x + dispersion * direction;
		targetY = data.y;

		data.matrix->findEmptyElement(data.x, data.y, targetX, targetY);

		if (data.x != targetX)
		{
			//we moving
			return data.matrix->swap(data.x, data.y, targetX, targetY);
		}

		//try again in other direction
		targetX = data.x - dispersion * direction;
		targetY = data.y;

		data.matrix->findEmptyElement(data.x, data.y, targetX, targetY);

		if (data.x != targetX)
		{
			//moving
			return data.matrix->swap(data.x, data.y, targetX, targetY);
		}

		//nothing, stuck
		return false;
	}

	//moving...

	return swap(data.x, data.y, targetX, targetY, *data.matrix);
}

bool Liquid::canSwap(Element* const other, int const xOffset, int const yOffset)
{
	//can swap if normal conditions, or if both liquids and the above is denser
	return Element::canSwap(other, xOffset, yOffset) || (other->getType() == Type::Liquid && yOffset >= 0 && getDensity() > other->getDensity());
}
