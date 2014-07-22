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
    T address;
    int size;
    int pointedBy;

    HeapNode(T d, int s=0,HeapNode<T> *parent = 0)
    {
        address = d;
        this->parent = parent;
        degree = 0;
        size = s;
        pointedBy = 1;
    }

};

#endif // HEAPNODE_H
