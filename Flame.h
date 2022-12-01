#ifndef FLAME_H
#define FLAME_H

#include "Vapor.h"

class Flame :
	public Vapor
{
protected:
	bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override;
	bool checkTemperature(Matrix::UpdateData const& data) override;

public:
	ID getID() const override { return ID::Flame; }
	std::string getName() const override { return "Flame"; }
	int getColor() const override { return 0x0099ffff; }
	float getDensity() const override { return 0.8f; }
	float getBaseTemperature() const override { return 340.0f; }
	float heatConductivity() const override { return 0.52f; }
	int convertOdds() const override { return 60; }
};

#endif
