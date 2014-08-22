#include "cuadradoflyweight.h"

CuadradoFlyweight::CuadradoFlyweight(Color c,double l)
{
    color = c;
    lado = l;
}

CuadradoFlyweight* CuadradoFlyweight::Instance = 0;

CuadradoFlyweight* CuadradoFlyweight::Init(Color c, double l)
{
    if (!Instance)
        Instance = new CuadradoFlyweight (c,l);
    return Instance;
}

double CuadradoFlyweight::getLado() const
{
    return lado;
}

void CuadradoFlyweight::setLado(double value)
{
    lado = value;
}


Color CuadradoFlyweight::getColor() const
{
    return color;
}

void CuadradoFlyweight::setColor(const Color &value)
{
    color = value;
}
