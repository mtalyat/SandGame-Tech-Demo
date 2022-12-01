#include "Rock.h"
#include "Molten.h"

bool Rock::checkTemperature(Matrix::UpdateData const& data)
{
    if (getTemperature() > 710.0f)
    {
        data.matrix->convertElement(data.x, data.y, new Molten(this), false);
        return true;
    }

    return false;
}
