#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include "StaticSolid.h"

//an static solid element that can conduct electricity
class Conductor :
    public StaticSolid
{
public:
    enum class CurrentDirection
    {
        None = 0,
        Up,
        Right,
        Down,
        Left
    };

protected:
    static const int DIRECTION_COUNT;
private:
    CurrentDirection direction;

private:
    void trySetCurrent(Element* const other, CurrentDirection const current, bool const updateToggle);

protected:
    Conductor(CurrentDirection const dir = CurrentDirection::None);

    bool onUpdate(Matrix::UpdateData const& data) override;

    //when electric, become yellow
    //otherwise do normal color
    virtual int getNonElectricColor() const = 0;
    int getColor() const override { return direction == CurrentDirection::None ? getNonElectricColor() : 0x00ffffff; }//electric color is yellow

public:
    SubType getSubType() const override { return SubType::Conductor; }

    void setCurrent(CurrentDirection const dir);
};

#endif
