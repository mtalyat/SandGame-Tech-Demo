#ifndef SAND_H
#define SAND_H

#include "DynamicSolid.h"

class Sand :
    public DynamicSolid
{
protected:
    bool onUpdate(Matrix::UpdateData const& data) override;
    bool reactWith(Element &other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
    bool checkTemperature(Matrix::UpdateData const& data) override;

public:
    ID getID() const override { return ID::Sand; }
    std::string getName() const override { return "Sand"; }
    int getColor() const override { return 0x00ffffff; }
    float getDensity() const override { return 10.0f; }
    float getBaseTemperature() const override { return BASE_TEMP; }
    int getFrictionOdds() const override { return 1; }
    int getFriction() const override { return 1; }
    int getDeflection() const override { return 4; }
    float heatConductivity() const override { return 0.6f; }
};

#endif