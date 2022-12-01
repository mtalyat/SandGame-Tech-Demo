#ifndef ROCK_H
#define ROCK_H

#include "DynamicSolid.h"

class Rock :
	public DynamicSolid
{
protected:
	bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
	bool checkTemperature(Matrix::UpdateData const& data) override;

public:
	ID getID() const override { return ID::Rock; }
	std::string getName() const override { return "Rock"; }
	int getColor() const override { return 0xa0a0a0ff; }
	float getDensity() const override { return 10.0f; }
	float getBaseTemperature() const override { return BASE_TEMP; }
	float heatConductivity() const override { return 0.6f; }
	int getFrictionOdds() const override { return 1; }
	int getFriction() const override { return 1; }
	int getDeflection() const override { return 2; }
};

#endif
