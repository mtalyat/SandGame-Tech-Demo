#include "Ash.h"

bool Ash::checkTemperature(Matrix::UpdateData const& data)
{
    if (getTemperature() > 1000.0f)
    {
        //if over xxx degrees, incinerate the ash
        data.matrix->destroyElement(data.x, data.y);
        return true;
    }

    return false;
}
