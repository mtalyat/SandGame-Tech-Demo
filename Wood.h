#ifndef WOOD_H
#define WOOD_H

#include "StaticSolid.h"

class Wood :
    public StaticSolid
{
protected:
    bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override;
    bool checkTemperature(Matrix::UpdateData const& data) override;

public:
    ID getID() const override { return ID::Wood; }
    std::string getName() const override { return "Wood"; }
    int getColor() const override { return 0x01244fff; }
    float getDensity() const override { return 2.0f; }
    float getBaseTemperature() const override { return BASE_TEMP; }
    int getFrictionOdds() const override { return 1; }
    int getFriction() const override { return 1; }
    float heatConductivity() const override { return 0.65f; }
};

#endif
