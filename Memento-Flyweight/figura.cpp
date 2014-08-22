#include "figura.h"


tipoFigura Figura::getTipo() const
{
    return tipo;
}

void Figura::setTipo(const tipoFigura &value)
{
    tipo = value;
}

double Figura::getX() const
{
    return X;
}

void Figura::setX(double value)
{
    X = value;
}

double Figura::getY() const
{
    return Y;
}

void Figura::setY(double value)
{
    Y = value;
}
