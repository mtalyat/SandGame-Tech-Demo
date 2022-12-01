#ifndef GAS_H
#define GAS_H

#include "Element.h"

class Gas :
	public Element
{
public:
	Type getType() const override { return Type::Gas; }
	virtual SubType getSubType() const override { return SubType::Gas; }
};

#endif