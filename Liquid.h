#ifndef LIQUID_H
#define LIQUID_H

#include "Element.h"

class Liquid :
	public Element
{
protected:
	virtual int getDispersion() const = 0;

	virtual bool onUpdate(Matrix::UpdateData const& data) override;

public:
	Type getType() const override { return Type::Liquid; }
	virtual SubType getSubType() const override { return SubType::Liquid; }

	virtual bool canSwap(Element* const other, int const xOffset, int const yOffset) override;
};

#endif // !LIQUID_H
