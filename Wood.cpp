#include "Wood.h"
#include "Fire.h"
#include "Ash.h"

bool Wood::reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data)
{
	return false;
}

bool Wood::checkTemperature(Matrix::UpdateData const& data)
{
	if (getTemperature() > 120.0f)
	{
		//combust!
		data.matrix->replaceElement(data.x, data.y, new Fire(this, Fire::Combustion::Random, new Ash(), 10), false);
	}

	return false;
}
