#include "circulo.h"

Circulo::Circulo(double x, double y, Color c, double r, tipoFigura t)
{
    this->X = x;
    this->Y = y;
    this->tipo = t;
    this->circuloFlyweight = CirculoFlyweight::Init(c,r);
}

Memento* Circulo::createMemento()
{
    Memento* m = new Memento (X, Y, circuloFlyweight->getColor(), circuloFlyweight->getRadio(), this);
    return m;
}

void Circulo::draw(QGraphicsScene *scene)
{
    QColor qcolor;
    QPen pen;

    if(circuloFlyweight->getColor() == rojo)
        qcolor = QColor (Qt::red);
    else if (circuloFlyweight->getColor() == azul)
        qcolor = QColor (Qt::blue);

    pen.setColor(qcolor);
    scene->addEllipse(X,Y,circuloFlyweight->getRadio(),circuloFlyweight->getRadio(),pen,QBrush(qcolor));

}

void Circulo::setColor(Color c)
{
    circuloFlyweight->setColor(c);
}

Color Circulo::getColor()
{
    return circuloFlyweight->getColor();
}

void Circulo::setRadio(double r)
{
    circuloFlyweight->setRadio(r);
}

double Circulo::getRadio()
{
    return circuloFlyweight->getRadio();
}

bool Circulo::wasClicked(double x, double y)
{
    double distance = sqrt(pow ((X - x),2) + pow((Y - y),2));
    return distance < circuloFlyweight->getRadio();
}
void Circulo::setMemento(Memento *m)
{
    this->X = m->getX();
    this->Y = m->getY();
    this->circuloFlyweight->setRadio(m->getRadio());
    this->circuloFlyweight->setColor(m->getColor());
}



