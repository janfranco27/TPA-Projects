#ifndef CIRCULO_H
#define CIRCULO_H

#include "figura.h"
#include "circuloflyweight.h"
class Circulo : public Figura
{
    CirculoFlyweight *circuloFlyweight;

public:
    Circulo(double x, double y, Color c, double r, tipoFigura t);
    void setMemento(Memento* m);
    Memento* createMemento();
    void draw(QGraphicsScene *scene);
    void setColor (Color c);
    Color getColor ();
    void setRadio (double r);
    double getRadio ();
    bool wasClicked(double x, double y);
};

#endif // CIRCULO_H
