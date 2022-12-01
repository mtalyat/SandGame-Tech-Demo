#include "Ice.h"
#include "Water.h"

bool Ice::checkTemperature(Matrix::UpdateData const& data)
{
    if (getTemperature() > 0.0f)
    {
        data.matrix->convertElement(data.x, data.y, new Water());
        return true;
    }

    return false;
}