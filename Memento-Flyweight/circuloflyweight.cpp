#include "circuloflyweight.h"

CirculoFlyweight::CirculoFlyweight(Color c, double r)
{
    color = c;
    radio = r;
}

CirculoFlyweight* CirculoFlyweight::Instance = 0;

CirculoFlyweight* CirculoFlyweight::Init(Color c, double r)
{
    if(!Instance)
        Instance = new CirculoFlyweight (c,r);
    return Instance;
}


double CirculoFlyweight::getRadio() const
{
    return radio;
}

void CirculoFlyweight::setRadio(double value)
{
    radio = value;
}


Color CirculoFlyweight::getColor() const
{
    return color;
}

void CirculoFlyweight::setColor(const Color &value)
{
    color = value;
}
