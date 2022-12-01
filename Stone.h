#ifndef STONE_H
#define STONE_H

#include "StaticSolid.h"

class Stone :
	public StaticSolid
{
protected:
	bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
	bool checkTemperature(Matrix::UpdateData const& data) override;

public:
	ID getID() const override { return ID::Stone; }
	std::string getName() const override { return "Stone"; }
	int getColor() const override { return 0xadadadff; }
	float getDensity() const override { return 10.0f; }
	float getBaseTemperature() const override { return BASE_TEMP; }
	int getFrictionOdds() const override { return 1; }
	int getFriction() const override { return 1; }
	float heatConductivity() const override { return 0.6f; }
};

#endif
