#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <utility>
#include "graph.h"

class Subject
{
public:
    std::vector < std::pair<double, double> > state;
    std::vector <Graph*> observers;

    static Subject* Init();
    void notify();
    void addObserver (Graph* observer);

    std::vector<std::pair<double, double> > getState() const;
    void setState(const std::vector<std::pair<double, double> > &value);

private:
    static Subject* instance;
    Subject();
};

#endif // SUBJECT_H
