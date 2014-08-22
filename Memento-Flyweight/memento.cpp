#include "memento.h"
#include "figura.h"
double Memento::getX() const
{
    return X;
}

void Memento::setX(double value)
{
    X = value;
}

double Memento::getY() const
{
    return Y;
}

void Memento::setY(double value)
{
    Y = value;
}

Color Memento::getColor() const
{
    return color;
}

void Memento::setColor(const Color &value)
{
    color = value;
}

double Memento::getRadio() const
{
    return radio;
}

void Memento::setRadio(double value)
{
    radio = value;
}
Memento::Memento(std::vector<Figura*> figuras, Color circulo, Color cuadrado)
{
    X = 0;
    Y = 0;
    radio = 0;
    state = figuras;
    circuloColor = circulo;
    cuadradoColor = cuadrado;
}

Memento::Memento(double x, double y, Color c, double r, Figura* f)
{
    this->X = x;
    this->Y = y;
    this->color = c;
    this->radio = r;
    state.push_back(f);
}

std::vector<Figura *> Memento::getState()
{
    int indice = -1;
    for(std::size_t i = 0; i < state.size(); i++)
    {
        if(state[i]->getTipo() == circulo)
        {
            indice = i;
            break;
        }
    }
    if(indice != -1)
        state[indice]->setColor(circuloColor);

    indice = -1;
    for(std::size_t i = 0; i < state.size(); i++)
    {
        if(state[i]->getTipo() == cuadrado)
        {
            indice = i;
            break;
        }
    }
    if(indice != -1)
        state[indice]->setColor(cuadradoColor);

    return state;
}

void Memento::setState(std::vector<Figura *> f)
{
    state = f;
}
