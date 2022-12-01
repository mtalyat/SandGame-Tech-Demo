#include "Spark.h"
#include "Conductor.h"

bool Spark::onUpdate(Matrix::UpdateData const& data)
{
    if (!Particle::onUpdate(data))
    {
        //if the spark stopped, delete
        data.matrix->destroyElement(data.x, data.y);
        return false;
    }

    //spark still moving
    return true;
}

bool Spark::reactWith(Element& other, int const xOffset, int const yOffset, Matrix::UpdateData const& data)
{
    //if hit a conductor, spread to it
    if (other.getSubType() == SubType::Conductor)
    {
        Conductor* conductor = static_cast<Conductor*>(&other);

        //assign based on direction
        if (yOffset < 0)
        {
            conductor->setCurrent(Conductor::CurrentDirection::Up);
        }
        else if (yOffset > 0)
        {
            conductor->setCurrent(Conductor::CurrentDirection::Down);
        }
        else if (xOffset > 0)
        {
            conductor->setCurrent(Conductor::CurrentDirection::Right);
        }
        else if (xOffset < 0)
        {
            conductor->setCurrent(Conductor::CurrentDirection::Left);
        }

        conductor->activate();
    }

    //after hitting anything, destroy itself
    data.matrix->destroyElement(data.x, data.y);

    return false;
}
