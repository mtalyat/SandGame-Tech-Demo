#include "Element.h"

const int Element::GRAVITY = 1;

const float Element::BASE_TEMP = 22.3f;

Element::Element()
	: state(0b00000010), temperature(0.0f), deltaTemperature(0.0f), xVel(0), yVel(0)
{
}

bool Element::interact(int const xOffset, int const yOffset, Matrix::UpdateData const& data)
{
	Element* other = data.matrix->getElement(data.x + xOffset, data.y + yOffset);

	if (!other)
	{
		//no element, no way to have reactions
		return false;
	}

	//otherwise try to react
	reactWith(*other, xOffset, yOffset, data);
}

void Element::trySpreadHeat(Element* const other)
{
	if (other)
	{
		other->applyHeat(*this);
	}
}

bool Element::swap(int const x, int const y, int const targetX, int const targetY, Matrix& matrix)
{
	if (matrix.swap(x, y, targetX, targetY)) {
		xVel = targetX - x;
		yVel = targetY - y;
		return true;
	}

	return false;
}

bool Element::trySwap(int const x, int const y, int const targetX, int const targetY, Matrix& matrix)
{
	Element* e = matrix.getElement(targetX, targetY);

	if (canSwap(e, targetX - x, targetY - y))
	{
		return swap(x, y, targetX, targetY, matrix);
	}

	return false;
}

void Element::init()
{
	temperature = getBaseTemperature();
}

bool Element::update(Matrix::UpdateData const& data)
{
	if (getUpdateToggle() != data.updateToggle)
	{
		//apply heat from last time
		temperature += deltaTemperature;
		deltaTemperature = 0.0f;

		//spread heat around
		trySpreadHeat(data.matrix->getElement(data.x + 1, data.y));
		trySpreadHeat(data.matrix->getElement(data.x - 1, data.y));
		trySpreadHeat(data.matrix->getElement(data.x, data.y + 1));
		trySpreadHeat(data.matrix->getElement(data.x, data.y - 1));

		//check if anything happened
		//if something did, do nothing
		if (!checkTemperature(data) && isActive())
		{
			//before custom update, apply gravity
			yVel += GRAVITY;

			//move the element
			bool active = onUpdate(data);

			//after moving in update, attempt to react with the surrounding elements
			active = interact(0, 1, data) || active;
			active = interact(0, -1, data) || active;
			active = interact(1, 0, data) || active;
			active = interact(-1, 0, data) || active;

			if (active)
			{
				//moved, try to set neighbors as active
				data.matrix->activateSurrounding(data.x, data.y);
			}
			else
			{
				//did not move or react, so deactivate
				deactivate();
			}

			setUpdateToggle(data.updateToggle);

			return active;
		}
	}

	//nothing happened: either already updated, or not active
	return false;
}

void Element::applyHeat(Element const& from)
{
	deltaTemperature += (from.getTemperature() - temperature) * from.heatConductivity() / (getDensity() + 1.0f) * Time::deltaTime;
}
