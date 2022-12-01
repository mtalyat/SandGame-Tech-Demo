#include "Vapor.h"

bool Vapor::onUpdate(Matrix::UpdateData const& data)
{
    //attempt to convert
    if (random_range(convertOdds()) == 0)
    {
        convert(data);
        return false;
    }
    
    //rise up
    //pick a random direction
    int direction = random_sign();

    //try to move up, in a direction
    if (canSwap(data.matrix->getElement(data.x + direction, data.y - 1), direction, -1) && data.matrix->swap(data.x, data.y, data.x + direction, data.y - 1))
    {
        return true;
    } else if (canSwap(data.matrix->getElement(data.x - direction, data.y - 1), -direction, -1) && data.matrix->swap(data.x, data.y, data.x - direction, data.y - 1))
    {
        return true;
    }
    
    //try to move left or right
    if (canSwap(data.matrix->getElement(data.x + direction, data.y), direction, 0) && data.matrix->swap(data.x, data.y, data.x + direction, data.y))
    {
        return true;
    }
    else if (canSwap(data.matrix->getElement(data.x - direction, data.y), -direction, 0) && data.matrix->swap(data.x, data.y, data.x - direction, data.y))
    {
        return true;
    }

    //always stay active as a gas
    return true;
}

bool Vapor::canSwap(Element* const other, int const xOffset, int const yOffset)
{
    //swap if this vapor is less dense and traveling up
    return Element::canSwap(other, xOffset, yOffset) || (other->getType() == Type::Gas && yOffset < 0 && getDensity() < other->getDensity());
}
