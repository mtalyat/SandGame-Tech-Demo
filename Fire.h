#ifndef FIRE_H
#define FIRE_H

#include "StaticSolid.h"

class Fire :
	public StaticSolid
{
public:
	enum class Combustion
	{
		None = 0,
		Random = 1,
		Linear = 2
	};

private:
	Element* burningElement;
	Element* dropElement;//most likely ash
	float longevity;
	int dropOdds;

protected:
	bool onUpdate(Matrix::UpdateData const& data) override;
	bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override;
	bool checkTemperature(Matrix::UpdateData const& data) override;

public:
	Fire(Element* const burning, Combustion const type, Element* const drop, int const dOdds = 1);
	~Fire();

	ID getID() const override { return ID::Fire; }
	std::string getName() const override { return "Fire"; }
	int getColor() const override { return 0x0048ffff; }
	float getDensity() const override { return burningElement->getDensity(); }
	float getBaseTemperature() const override { return 420.0f; }
	float heatConductivity() const override { return 0.70f; }
	int getFrictionOdds() const override { return 1; }
	int getFriction() const override { return 0; }
};

#endif
