#ifndef CIRCULOFLYWEIGHT_H
#define CIRCULOFLYWEIGHT_H
#include "figura.h"

class CirculoFlyweight
{
private:
    Color color;
    double radio;
    CirculoFlyweight(Color c, double r);
    static CirculoFlyweight *Instance;

public:
    static CirculoFlyweight* Init(Color c, double r);

    Color getColor() const;
    void setColor(const Color &value);
    double getRadio() const;
    void setRadio(double value);
};

#endif // CIRCULOFLYWEIGHT_H
