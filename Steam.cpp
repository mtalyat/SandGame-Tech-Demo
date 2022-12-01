#include "Steam.h"
#include "Water.h"

bool Steam::checkTemperature(Matrix::UpdateData const& data)
{
    if (getTemperature() < 97.0f)
    {
        convert(data);
        return true;
    }

    return false;
}

void Steam::convert(Matrix::UpdateData const& data)
{
    data.matrix->replaceElement(data.x, data.y, new Water());
}
