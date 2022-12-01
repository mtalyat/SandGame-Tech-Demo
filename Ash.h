#ifndef ASH_H
#define ASH_H

#include "Particle.h"

class Ash :
	public Particle
{
protected:
	bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
	bool checkTemperature(Matrix::UpdateData const& data) override;

public:
	ID getID() const override { return ID::Ash; }
	std::string getName() const override { return "Ash"; }
	int getColor() const override { return 0x52585Eff; }
	float getDensity() const override { return 0.2f; }
	float getBaseTemperature() const override { return BASE_TEMP; }
	float heatConductivity() const override { return 0.21f; }
	int getFrictionOdds() const override { return 5; }
	int getFriction() const override { return 1; }
	int getDeflection() const override { return 0; }
};

#endif
