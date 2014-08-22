#include "graphpoints.h"
#include "subject.h"


GraphPoints::GraphPoints()
{
    subject = Subject::Init();
}

void GraphPoints::dibujar()
{
    scene = new QGraphicsScene ();
    std::vector < std::pair <double, double> > state = subject->getState();
    QPen pen;
    pen.setColor(QColor (Qt::red));
    for (int i = 0; i < state.size(); i++)
    {
        scene->addEllipse(state[i].first, state[i].second, 5, 5, pen, QBrush (QColor (Qt::red)) );
    }
}
