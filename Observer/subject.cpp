#include "subject.h"

Subject* Subject::instance = 0;


Subject::Subject()
{
}


std::vector<std::pair<double, double> > Subject::getState() const
{
    return state;
}

void Subject::setState(const std::vector<std::pair<double, double> > &value)
{
    state = value;
}
Subject *Subject::Init()
{
    if (!instance)
        instance = new Subject();
    return instance;
}

void Subject::notify()
{
    for(size_t i = 0; i < observers.size(); i++)
    {
        observers[i]->notificado();
    }
}

void Subject::addObserver(Graph *observer)
{
    observers.push_back(observer);
}

