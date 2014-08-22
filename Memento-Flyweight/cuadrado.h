#ifndef CUADRADO_H
#define CUADRADO_H

#include "figura.h"
#include "cuadradoflyweight.h"

class Cuadrado : public Figura
{
private:
    CuadradoFlyweight* cuadradoFlyweight;

public:
    Cuadrado(double x, double y, Color c, double l, tipoFigura t);
    void setMemento(Memento* m);
    Memento* createMemento();
    void draw (QGraphicsScene* scene);
    void setColor (Color c);
    Color getColor ();
    void setRadio (double r);
    double getRadio ();
    bool wasClicked(double x, double y);


};

#endif // CUADRADO_H
