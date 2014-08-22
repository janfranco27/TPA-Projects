#ifndef CARETAKER_H
#define CARETAKER_H

#include <stack>
#include "memento.h"
class CareTaker
{
private:
    std::stack<Memento*> undoStack;
    std::stack<Memento*> redoStack;

public:
    CareTaker();
    void addMemento(Memento *m);
    std::vector<Figura*> undo();
    std::vector<Figura*> redo();
    bool canRedo();
};

#endif // CARETAKER_H
