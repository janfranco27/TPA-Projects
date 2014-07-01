#include <iostream>
#include <list>
#include<fstream>
#include <FibonacciHeap.h>

using namespace std;

ofstream file;

template<class T>
void printHeapNode (FibonacciNode<T> *node)
{
    typename list<FibonacciNode<T> *>::iterator sons = node->sons.begin();
    if(sons == node->sons.end()) file<<node->key<<";"<<endl;
    for(;sons != node->sons.end(); ++sons)
    {
        file<<node->key<<" -> " << (*sons)->key << ";" << endl;
        printHeapNode(*sons);
    }
}


template<class T>
void printPaintedNode (FibonacciNode<T> *node)
{
    typename list<FibonacciNode<T> *>::iterator sons = node->sons.begin();
    if(sons == node->sons.end() && node->marked) file<<node->key<<" [style=filled fillcolor=red]"<<endl;
    for(;sons != node->sons.end(); ++sons)
    {
        if((*sons)->marked)
            file<<(*sons)->key <<" [style=filled fillcolor=red]"<<endl;
        printPaintedNode(*sons);
    }
}

template<class T>
void printPaintedNodes (FibonacciHeap<T> &heap)
{
    file <<"{"<<endl;
    typename list<FibonacciNode<T> *>::iterator heapIterator = heap.headList.begin();
    for(;heapIterator != heap.headList.end(); ++heapIterator)
    {
        if((*heapIterator)->marked)
            file <<(*heapIterator)->key<<" [style=filled fillcolor=red]"<<endl;
        printPaintedNode (*heapIterator);
    }
    file <<"}"<<endl;
}


template<class T>
void printHeap (FibonacciHeap<T> &heap)
{
    file << "digraph G {"<<endl;

    printPaintedNodes(heap);
    typename list<FibonacciNode<T> *>::iterator heapIterator = heap.headList.begin();
    for(;heapIterator != heap.headList.end(); ++heapIterator)
    {
        printHeapNode (*heapIterator);
    }
    file << "}"<<endl;
}

int main()
{
    file.open("fibonacciHeap.txt");
    FibonacciHeap<int> heap;

    for(int i = 0; i < 1000; i++)
        heap.insert(i);

    cout<<"minimo "<<heap.getMinimumKey()<<endl;
    heap.extractMin();
    cout<<"minimo "<<heap.getMinimumKey()<<endl;

    heap.decreaseKey(999,-2);
    cout<<"minimo "<<heap.getMinimumKey()<<endl;

    printHeap(heap);
    file.close();
    return 0;
}

