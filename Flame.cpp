#include "Flame.h"

bool Flame::reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data)
{
    //if hit water, extinguish entirely
    if (other.getID() == ID::Water)
    {
        data.matrix->destroyElement(data.x, data.y);
        return true;
    }

    return false;
}

bool Flame::checkTemperature(Matrix::UpdateData const& data)
{
    if (getTemperature() < 120.0f)
    {
        //no more flame
        data.matrix->destroyElement(data.x, data.y);
        return true;
    }

    return false;
}
