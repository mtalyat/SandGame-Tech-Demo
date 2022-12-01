#ifndef IRON_H
#define IRON_H

#include "Conductor.h"

class Iron :
    public Conductor
{
protected:
    virtual bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
    virtual bool checkTemperature(Matrix::UpdateData const& data) override { return false; }

public:
    virtual ID getID() const override { return ID::Iron; }
    virtual std::string getName() const override { return "Iron"; }
    virtual float getDensity() const override { return 15.0f; }
    virtual float getBaseTemperature() const override { return BASE_TEMP; }
    virtual float heatConductivity() const override { return 1.0f; }
    virtual int getFrictionOdds() const override { return 8; }
    virtual int getFriction() const override { return 1; }
    virtual int getNonElectricColor() const override { return 0xb5b9c7ff; }
};

#endif
