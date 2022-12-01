#ifndef VAPOR_H
#define VAPOR_H

#include "Gas.h"

//gasses that rise upwards
class Vapor :
	public Gas
{
protected:
	virtual bool onUpdate(Matrix::UpdateData const& data) override;

	virtual int convertOdds() const = 0;

	virtual void convert(Matrix::UpdateData const& data) { data.matrix->destroyElement(data.x, data.y); }

public:
	bool canSwap(Element* const other, int const xOffset, int const yOffset) override;

	virtual SubType getSubType() const override { return SubType::Vapor; }

};

#endif
