#include "cuadrado.h"

Cuadrado::Cuadrado(double x, double y, Color c, double l, tipoFigura t)
{
    this->X = x;
    this->Y = y;
    this->tipo = t;
    this->cuadradoFlyweight = CuadradoFlyweight::Init(c, l);
}

Memento* Cuadrado::createMemento()
{
    Memento* m = new Memento (X, Y, cuadradoFlyweight->getColor(), cuadradoFlyweight->getLado(), this);
    return m;
}

void Cuadrado::draw(QGraphicsScene *scene)
{

    QColor qcolor;
    QPen pen;

    if(cuadradoFlyweight->getColor() == rojo)
        qcolor = QColor (Qt::red);
    else if (cuadradoFlyweight->getColor() == azul)
        qcolor = QColor (Qt::blue);

    pen.setColor(qcolor);
    scene->addRect(X,Y,cuadradoFlyweight->getLado(),cuadradoFlyweight->getLado(),pen,QBrush(qcolor));

}

void Cuadrado::setColor(Color c)
{
    cuadradoFlyweight->setColor(c);
}

Color Cuadrado::getColor()
{
    return cuadradoFlyweight->getColor();
}

void Cuadrado::setRadio(double r)
{
    cuadradoFlyweight->setLado(r);
}

double Cuadrado::getRadio()
{
    return cuadradoFlyweight->getLado();
}

bool Cuadrado::wasClicked(double x, double y)
{
    double distance = sqrt(pow ((X - x),2) + pow((Y - y),2));
    return distance < cuadradoFlyweight->getLado() / 2;
}
void Cuadrado::setMemento(Memento *m)
{
    this->X = m->getX();
    this->Y = m->getY();
    this->cuadradoFlyweight->setLado(m->getRadio());
    this->cuadradoFlyweight->setColor(m->getColor());
}
