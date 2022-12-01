#pragma once
#include "Particle.h"
class Spark :
    public Particle
{
protected:
    bool onUpdate(Matrix::UpdateData const& data) override;
    virtual bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override;
    virtual bool checkTemperature(Matrix::UpdateData const& data) override { return false; }

public:
    virtual ID getID() const override { return ID::Spark; }
    virtual std::string getName() const override { return "Spark"; }
    virtual int getColor() const override { return 0x70f1ffff; }
    virtual float getDensity() const override { return 0.0011f; }
    virtual float getBaseTemperature() const override { return BASE_TEMP; }
    virtual float heatConductivity() const override { return 0.5f; }
    virtual int getFrictionOdds() const override { return 1; }
    virtual int getFriction() const override { return 0; }
    virtual int getDeflection() const override { return 0; }
};

