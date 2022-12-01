#ifndef MOLTEN_H
#define MOLTEN_H

#include "Liquid.h"

class Molten :
    public Liquid
{
private:
    Element* const solidElement;
    Element* const cooledElement;
protected:
    bool reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) override { return false; }
    bool checkTemperature(Matrix::UpdateData const& data) override;

public:
    //default to lava
    Molten(Element *const sElement = nullptr, Element *const cElement = nullptr);
    ~Molten();

    ID getID() const override { return ID::Molten; }
    std::string getName() const override { return ((!solidElement || solidElement->getID() == ID::Rock) ? "Lava" : "Molten " + solidElement->getName()); }
    int getColor() const override { return 0x0544e6ff; }
    float getDensity() const override { return solidElement ? solidElement->getDensity() : 10.0f; }
    float getBaseTemperature() const override { return BASE_TEMP + 1500.0f; }
    int getDispersion() const override { return 1; }
    float heatConductivity() const override { return 0.24f; }
};

#endif
