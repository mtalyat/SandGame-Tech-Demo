#ifndef STEAM_H
#define STEAM_H

#include "Vapor.h"

class Steam :
    public Vapor
{
protected:
    bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
    bool checkTemperature(Matrix::UpdateData const& data) override;
    int convertOdds() const override { return 1200; }//20 seconds avg lifetime
    void convert(Matrix::UpdateData const& data) override;
public:
    ID getID() const override { return ID::Steam; }
    std::string getName() const override { return "Steam"; }
    int getColor() const override { return 0xffffffff; }
    float getDensity() const override { return 0.02f; }
    float getBaseTemperature() const override { return 122.0f; }
    float heatConductivity() const override { return 0.19f; }
};

#endif
