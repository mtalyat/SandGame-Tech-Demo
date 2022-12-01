#include "Molten.h"
#include "Rock.h"

Molten::Molten(Element *const sElement, Element* const cElement)
    :Liquid::Liquid(), solidElement(sElement), cooledElement((!cElement) ? sElement : cElement)
{
}

Molten::~Molten()
{
    //delete solid element, not cooled
    //cooled is now within the world, but solid is gone forever
    //so long as solid != cooled
    if (solidElement && solidElement != cooledElement)
    {
        delete solidElement;
    }
}

bool Molten::checkTemperature(Matrix::UpdateData const& data)
{
    if (getTemperature() < 500.0f)
    {
        //default is rock, so the element will fall after it has cooled off (otherwise stone just hangs on the surface)
        data.matrix->convertElement(data.x, data.y, cooledElement ? cooledElement : new Rock());
        return true;
    }

    return false;
}
