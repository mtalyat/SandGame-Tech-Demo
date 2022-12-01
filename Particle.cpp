#include "Particle.h"

bool Particle::onUpdate(Matrix::UpdateData const& data)
{
    //fall like the opposite of vapor
    int direction = random_sign();

    //try to move down, in a direction
    if (canSwap(data.matrix->getElement(data.x + direction, data.y + 1), direction, 1) && data.matrix->swap(data.x, data.y, data.x + direction, data.y + 1))
    {
        return true;
    }
    else if (canSwap(data.matrix->getElement(data.x - direction, data.y + 1), -direction, 1) && data.matrix->swap(data.x, data.y, data.x - direction, data.y + 1))
    {
        return true;
    }

    return false;
}
