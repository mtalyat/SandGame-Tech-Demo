#include "Fire.h"
#include "Flame.h"

bool Fire::onUpdate(Matrix::UpdateData const& data)
{
	//try to spawn flames around the fire
	if (random_range(20) == 0)
	{
		//always do top, then a side, then the bottom
		if (data.matrix->trySetElement<Flame>(data.x, data.y - 1))//up
		{
		}
		else
		{
			int direction = random_sign();

			if (data.matrix->trySetElement<Flame>(data.x + direction, data.y))//side
			{

			}
			else if (data.matrix->trySetElement<Flame>(data.x - direction, data.y))//other side
			{

			}
			else if (data.matrix->trySetElement<Flame>(data.x, data.y + 1))//down
			{

			}
		}
	}

	//check life
	if (longevity <= 0.0f)
	{
		//die (burnt out)
		if (random_range(dropOdds) == 0)
		{
			data.matrix->replaceElement(data.x, data.y, dropElement);
			dropElement = nullptr;
		}
		else
		{
			//did not drop the element, just destroy
			data.matrix->destroyElement(data.x, data.y);
		}

		return false;
	}

	//decrease life timer
	longevity -= Time::deltaTime;

	//always stay active
	return true;
}

bool Fire::reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data)
{
	//if hit water, extinguish
	if (other.getID() == ID::Water)
	{
		//data.matrix->destroyElement(data.x, data.y);
		data.matrix->replaceElement(data.x, data.y, burningElement);
		burningElement = nullptr;
		return true;
	}

	return false;
}

bool Fire::checkTemperature(Matrix::UpdateData const& data)
{
	//if temp drops below 200, remove entirely
	if (getTemperature() < 200.0f)
	{
		//fire is also dead
		//data.matrix->destroyElement(data.x, data.y);
		data.matrix->replaceElement(data.x, data.y, burningElement);
		burningElement = nullptr;
		return true;
	}

	return false;
}

Fire::Fire(Element* const burning, Combustion const type, Element* const drop, int const dOdds)
	: burningElement(burning), longevity(0.0f), dropElement(drop), dropOdds(std::max(1, dOdds))
{
	if (burningElement)
	{
		//it is not doing anything
		burningElement->deactivate();
	}

	//fire longevity determined based on the burning material's density, as well as the given Combustion
	if (burningElement)
	{
		switch (type)
		{
		case Combustion::Linear:
			longevity = burningElement->getDensity() * 2.0f;
			break;
		case Combustion::Random:
			longevity = burningElement->getDensity() + random_range(0.0f, burning->getDensity());
			break;
		default:
			//if no type, just despawn ig
			break;
		}
	}
}

Fire::~Fire()
{
	//destroy the burning element, if it is not back within the world
	if (burningElement)
	{
		//if it is not extinquished, destroy
		delete burningElement;
	}

	if (dropElement)
	{
		delete dropElement;
	}
}
