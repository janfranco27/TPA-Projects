#ifndef FIBONACCINODE_H
#define FIBONACCINODE_H

#include<list>
using namespace std;

template <class T>

class FibonacciNode
{
private:

public:
    int degree;
    bool marked;
    FibonacciNode<T> *parent;
    list <FibonacciNode<T> *> sons;
    T key;
    FibonacciNode(T d, FibonacciNode<T> *parent = 0)
    {
        key = d;
        this->parent = parent;
        degree = 0;
        marked = false;
    }

    bool operator ==(FibonacciNode<T> &node2)
    {
        return key == node2.key;
    }

    bool operator <(FibonacciNode<T> &node2)
    {
        return key < node2.key;
    }
};


#endif // FIBONACCINODE_H
