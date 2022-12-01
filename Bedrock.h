#ifndef BEDROCK_H
#define BEDROCK_H

#include "StaticSolid.h"

class Bedrock :
    public StaticSolid
{
private:
    bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }

public:
    ID getID() const override { return ID::Bedrock; }
    std::string getName() const override { return "Bedrock"; }
    int getColor() const override { return 0x4d4d4dff; }
    float getDensity() const override { return INT_MAX; }
    float getBaseTemperature() const override { return BASE_TEMP; }
    int getFrictionOdds() const override { return 1; }
    int getFriction() const override { return 1; }
    bool checkTemperature(Matrix::UpdateData const& data) override { return false; }
    float heatConductivity() const override { return 0.6f; }
};

#endif
