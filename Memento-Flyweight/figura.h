#ifndef FIGURA_H
#define FIGURA_H

#include "memento.h"
#include "math.h"

#include <QGraphicsScene>

class Figura
{
protected:
    double X, Y;
    tipoFigura tipo;

public:
    //Figura(int x, int y, tipoFigura t);
    tipoFigura getTipo() const;
    void setTipo(const tipoFigura &value);
    double getX() const;
    void setX(double value);
    double getY() const;
    void setY(double value);

    virtual Memento* createMemento () = 0;
    virtual void setMemento (Memento* m) = 0;
    virtual void draw (QGraphicsScene* scene) = 0;
    virtual void setColor (Color c) = 0;
    virtual Color getColor () = 0;
    virtual void setRadio (double r) = 0;
    virtual double getRadio () = 0;
    virtual bool wasClicked (double x, double y) = 0;
};

#endif // FIGURA_H
