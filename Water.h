#ifndef WATER_H
#define WATER_H

#include "Liquid.h"

class Water :
    public Liquid
{
protected:
    bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override;
    bool checkTemperature(Matrix::UpdateData const& data) override;

public:
    ID getID() const override { return ID::Water; }
    std::string getName() const override { return "Water"; }
    int getColor() const override { return 0xff0000ff; }
    float getDensity() const override { return 1.0f; }
    float getBaseTemperature() const override { return BASE_TEMP; }
    int getDispersion() const override { return 5; }
    float heatConductivity() const override { return 0.11f; }
};

#endif
