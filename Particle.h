#ifndef PARTICLE_H
#define PARTICLE_H

#include "DynamicSolid.h"

class Particle :
    public DynamicSolid
{
protected:
    virtual bool onUpdate(Matrix::UpdateData const& data) override;

public:
    virtual SubType getSubType() const override { return SubType::Particle; }
};

#endif
