#include "Water.h"
#include "Sand.h"
#include "Steam.h"
#include "Ice.h"

bool Water::reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data)
{
    //if stone, chance to turn it into sand
    switch (other.getID())
    {
    case ID::Stone:
        if (random_range(600) == 0)
        {
            //combine with the stone to turn it into sand
            data.matrix->convertElement(data.x + xOffset, data.y + yOffset, new Sand());
            data.matrix->destroyElement(data.x, data.y);
        }
        break;
    default:
        return false;
    }

    return true;
}

bool Water::checkTemperature(Matrix::UpdateData const& data)
{
    if (getTemperature() > 100.0f)
    {
        data.matrix->convertElement(data.x, data.y, new Steam());
        return true;
    }
    else if (getTemperature() < 0.0f)
    {
        data.matrix->convertElement(data.x, data.y, new Ice());
        return true;
    }
    
    return false;
}
