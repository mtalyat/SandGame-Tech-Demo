#ifndef DYNAMICSOLID_H
#define DYNAMICSOLID_H

#include "Solid.h"

//powder class
class DynamicSolid :
	public Solid
{
protected:
	virtual bool onUpdate(Matrix::UpdateData const& data) override;

	virtual int getDeflection() const = 0;//default 4

public:
	virtual SubType getSubType() const override { return SubType::Powder; }
};

#endif