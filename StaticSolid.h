#ifndef STATICSOLID_H
#define STATICSOLID_H

#include "Solid.h"

class StaticSolid :
	public Solid
{
protected:
	virtual bool onUpdate(Matrix::UpdateData const& data) override;
};

#endif