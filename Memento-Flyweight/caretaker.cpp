#include "caretaker.h"

CareTaker::CareTaker()
{

}

void CareTaker::addMemento(Memento *m)
{
    undoStack.push(m);
    redoStack = std::stack<Memento*>();
}

std::vector<Figura*> CareTaker::undo()
{
    std::vector<Figura*> f;
    if(undoStack.size() != 0)
    {
        redoStack.push(undoStack.top());
        undoStack.pop();
        if (undoStack.size() == 0) return f;
        Memento *m = undoStack.top();
        return m->getState();
    }
    else return f;
}


std::vector<Figura*> CareTaker::redo()
{
        Memento *m = redoStack.top();
        undoStack.push(m);
        redoStack.pop();
        return m->getState();

}

bool CareTaker::canRedo()
{
    return redoStack.size() > 0;
}

