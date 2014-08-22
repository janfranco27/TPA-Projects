#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsView>

class Subject;

class Graph
{
public:
    Graph();
    QGraphicsScene* scene;
    Subject* subject;

    void notificado();
    virtual void dibujar() = 0;
};

#endif // GRAPH_H
