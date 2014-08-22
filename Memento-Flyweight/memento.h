#ifndef MEMENTO_H
#define MEMENTO_H

#include <vector>
class Figura;

enum Color  {rojo = 0, azul = 1};
enum tipoFigura  {circulo = 0, cuadrado = 1};


class Memento
{
private:
    double X, Y;
    Color color;
    double radio;
    std::vector<Figura*> state;
    Color circuloColor;
    Color cuadradoColor;
public:
    Memento(std::vector<Figura*> figuras, Color circulo, Color cuadrado);
    Memento(double x, double y, Color c, double r, Figura* t);
    std::vector<Figura*> getState ();
    void setState (std::vector<Figura*> f);

    double getX() const;
    void setX(double value);
    double getY() const;
    void setY(double value);
    Color getColor() const;
    void setColor(const Color &value);
    double getRadio() const;
    void setRadio(double value);
};

#endif // MEMENTO_H
