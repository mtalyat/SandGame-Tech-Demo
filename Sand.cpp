#include "Sand.h"
#include "Molten.h"
#include "Glass.h"

bool Sand::onUpdate(Matrix::UpdateData const& data)
{
	//if moved, return true
	if (DynamicSolid::onUpdate(data))
	{
		return true;
	}

	//didn't move...

	//if cannot move down, try moving to the sides
	int direction = random_sign();

	if (!data.matrix->getElement(data.x + direction, data.y) && !data.matrix->getElement(data.x + direction, data.y + 1))
	{
		return swap(data.x, data.y, data.x + direction, data.y + 1, *data.matrix);
	}
	else if (!data.matrix->getElement(data.x - direction, data.y) && !data.matrix->getElement(data.x - direction, data.y + 1))
	{
		return swap(data.x, data.y, data.x - direction, data.y + 1, *data.matrix);
	}

	//else do nothing

	return false;
}

bool Sand::checkTemperature(Matrix::UpdateData const& data)
{
	if (getTemperature() > 710.0f)
	{
		data.matrix->convertElement(data.x, data.y, new Molten(this, new Glass()), false);
		return true;
	}

	return false;
}
