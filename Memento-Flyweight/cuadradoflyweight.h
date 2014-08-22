#ifndef CUADRADOFLYWEIGHT_H
#define CUADRADOFLYWEIGHT_H

#include "figura.h"
class CuadradoFlyweight
{
private:
    double lado;
    Color color;
    CuadradoFlyweight (Color c, double l);
    static CuadradoFlyweight* Instance;

public:
    static CuadradoFlyweight* Init (Color c, double l);
    Color getColor() const;
    void setColor(const Color &value);
    double getLado() const;
    void setLado(double value);
};

#endif // CUADRADOFLYWEIGHT_H
