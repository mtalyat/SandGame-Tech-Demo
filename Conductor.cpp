#include "Conductor.h"

const int Conductor::DIRECTION_COUNT = 4;

void Conductor::trySetCurrent(Element* const other, CurrentDirection const current, bool const updateToggle)
{
	if (other && other->getSubType() == SubType::Conductor)
	{
		Conductor* const conductor = static_cast<Conductor*>(other);

		conductor->activate();
		conductor->setCurrent(current);
		conductor->setUpdateToggle(updateToggle);
	}
}

Conductor::Conductor(CurrentDirection const dir)
	: direction(dir)
{
}

bool Conductor::onUpdate(Matrix::UpdateData const& data)
{
	//if this element has a current, spread it
	if (direction != CurrentDirection::None)
	{
		//do not spread backwards, but spread the other directions
		int backwards = ((int)direction - 1 + (DIRECTION_COUNT / 2)) % DIRECTION_COUNT;

		for (int i = 0; i < DIRECTION_COUNT; i++)
		{
			if (i != backwards)
			{
				switch (i)
				{
				case 0://up
					trySetCurrent(data.matrix->getElement(data.x, data.y - 1), CurrentDirection::Up, data.updateToggle);
					break;
				case 1://right
					trySetCurrent(data.matrix->getElement(data.x + 1, data.y), CurrentDirection::Right, data.updateToggle);
					break;
				case 2://down
					trySetCurrent(data.matrix->getElement(data.x, data.y + 1), CurrentDirection::Down, data.updateToggle);
					break;
				case 3://left
					trySetCurrent(data.matrix->getElement(data.x - 1, data.y), CurrentDirection::Left, data.updateToggle);
					break;
				}
			}
		}

		//now remove self
		direction = CurrentDirection::None;

		return true;
	}

	return false;
}

void Conductor::setCurrent(CurrentDirection const dir)
{
	//if not empty, cancel
	if (direction != CurrentDirection::None && dir != CurrentDirection::None)
	{
		direction = CurrentDirection::None;
	}
	else
	{
		direction = dir;
	}
}
