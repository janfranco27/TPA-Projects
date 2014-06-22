#ifndef HEAPNODE_H
#define HEAPNODE_H

#include<list>

using namespace std;
template <class T>

class HeapNode
{
private:

public:
    int degree;
    HeapNode<T> *parent;
    list <HeapNode<T> *> sons;
    T key;
    HeapNode(T d, HeapNode<T> *parent = 0)
    {
        key = d;
        this->parent = parent;
        degree = 0;
    }
};

#endif // HEAPNODE_H
