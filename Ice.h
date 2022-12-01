#ifndef ICE_H
#define ICE_H

#include "DynamicSolid.h"

class Ice :
	public DynamicSolid
{
protected:
	bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
	bool checkTemperature(Matrix::UpdateData const& data) override;

public:
	ID getID() const override { return ID::Ice; }
	std::string getName() const override { return "Ice"; }
	int getColor() const override { return 0xff770075; }
	float getDensity() const override { return 1.0f; }
	float getBaseTemperature() const override { return -21.1; }
	float heatConductivity() const override { return 0.184; }
	int getFrictionOdds() const override { return 100; }
	int getFriction() const override { return 1; }
	int getDeflection() const override { return 3; }
};

#endif
