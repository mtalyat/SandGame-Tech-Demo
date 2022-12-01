#include "Stone.h"
#include "Molten.h"
#include "Rock.h"

bool Stone::checkTemperature(Matrix::UpdateData const& data)
{
    if (getTemperature() > 710.0f)
    {
        data.matrix->convertElement(data.x, data.y, new Molten(this, new Rock()), false);
        return true;
    }

    return false;
}
