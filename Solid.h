#ifndef SOLID_H
#define SOLID_H

#include "Element.h"

class Solid :
	public Element
{
public:
	Type getType() const override { return Type::Solid; }
	virtual SubType getSubType() const override { return SubType::Solid; }

	virtual bool canSwap(Element* const other, int const xOffset, int const yOffset) override { return !other || (getType() > other->getType() && getDensity() > other->getDensity()); }

	virtual int getFrictionOdds() const = 0;//default 1
	virtual int getFriction() const = 0;//default 1
};

#endif