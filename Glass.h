#ifndef GLASS_H
#define GLASS_H

#include "StaticSolid.h"

class Glass :
    public StaticSolid
{
protected:
    bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
    bool checkTemperature(Matrix::UpdateData const& data) override { return false; }

public:
    ID getID() const override { return ID::Glass; }
    std::string getName() const override { return "Glass"; }
    int getColor() const override { return 0xffffff75; }
    float getDensity() const override { return 0.1f; }
    float getBaseTemperature() const override { return BASE_TEMP; }
    float heatConductivity() const override { return 0.6f; }
    int getFrictionOdds() const override { return 10; }
    int getFriction() const override { return 1; }
};

#endif
