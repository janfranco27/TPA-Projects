#include "graphline.h"
#include "subject.h"

GraphLine::GraphLine()
{
    subject = Subject::Init();
}

void GraphLine::dibujar()
{
    scene = new QGraphicsScene ();
    std::vector < std::pair <double, double> > state = subject->getState();
    QPen pen;
    pen.setColor(QColor (Qt::red));
    for (int i = 0; i < state.size() - 1; i++)
    {
        scene->addLine(state[i].first, state[i].second, state[i+1].first, state[i+1].second, pen);
    }
}
