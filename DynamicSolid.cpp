#include "DynamicSolid.h"
#include "Liquid.h"

bool DynamicSolid::onUpdate(Matrix::UpdateData const& data)
{
	int targetX = data.x + xVel;
	int targetY = data.y + yVel;
	int tX = targetX;
	int tY = targetY;

	data.matrix->findEmptyElement(data.x, data.y, targetX, targetY);

	if (data.x == targetX && data.y == targetY)
	{
		//did not move, check for below
		if (trySwap(data.x, data.y, data.x, data.y + 1, *data.matrix))
		{
			//did move
			return true;
		}
		else {
			//cannot move
			xVel = 0;
			yVel = 0;
			return false;
		}
	}

	//moving...

	if (tX != targetX && yVel > 0)
	{
		//slowing down, use friction
		Element* e = data.matrix->getElement(targetX, targetY + 1);

		//test self
		if (random_range(getFrictionOdds()) == 0)
		{
			if (xVel > 0)
			{
				xVel = std::max(0, xVel - (getFriction()));
			}
			else {
				xVel = std::min(0, xVel + (getFriction()));
			}
		}

		//set collision
		if (e && e->getType() == Type::Solid)
		{
			Solid* s = static_cast<Solid*>(e);

			if (random_range(s->getFrictionOdds()) == 0)
			{
				if (xVel > 0)
				{
					xVel = std::max(0, xVel - (s->getFriction()));
				}
				else {
					xVel = std::min(0, xVel + (s->getFriction()));
				}
			}
		}
	}

	if (tY != targetY)
	{
		//hit something...
		int dir;
		if (xVel < 0)
		{
			dir = -1;
		}
		else if (xVel > 0)
		{
			dir = 1;
		}
		else {
			dir = random_sign();
		}

		if (trySwap(data.x, data.y, targetX, targetY, *data.matrix)) {
			//convert some to horizontal energy
			xVel += abs(yVel) / getDeflection() * dir;
			yVel = 0;

			return true;
		}
		
		return false;
	}
	else {
		//hit nothing
		return trySwap(data.x, data.y, targetX, targetY, *data.matrix);
	}

	
}
