#include <iostream>
#include <fstream>
#include <binomialheap.h>
#include <vector>

using namespace std;

ofstream file;

template<class T>
void printHeapNode (HeapNode<T> *node)
{
    typename list<HeapNode<T> *>::iterator sons = node->sons.begin();
    if(sons == node->sons.end()) file<<node->key<<";"<<endl;
    for(;sons != node->sons.end(); ++sons)
    {
        file<<node->key<<" -> " << (*sons)->key << ";" << endl;
        printHeapNode(*sons);
    }
}

template<class T>
void printHeap (BinomialHeap<T> &heap)
{
    file << "digraph G {"<<endl;
    typename list<HeapNode<T> *>::iterator heapIterator = heap.headList.begin();
    for(;heapIterator != heap.headList.end(); ++heapIterator)
    {
        printHeapNode (*heapIterator);
    }
    //file <<"minValue -> " << (*(heap.minValue))->key <<";"<<endl;
    file << "}"<<endl;
}

int main()
{
    file.open("binomialHeap.txt");
    time_t start, stop;

    BinomialHeap<int> heap;

    for(int i = 1; i < 10; i++)
       heap.insert(i);


    start = clock();
    cout<<"MINIMO: "<<heap.getMinimumKey()<<endl;
    heap.extractMin();
    cout<<"MINIMO luego de extraccion: "<<heap.getMinimumKey()<<endl;
    stop = clock();
    cout << "List iteration: " << (double)(stop-start)/CLOCKS_PER_SEC <<endl;

    heap.decreaseKey(8,-4);
    heap.deleteNode(5, -100000);
    cout<<"MINIMO luego de extraccion: "<<heap.getMinimumKey()<<endl;

    printHeap(heap);
    file.close();
    return 0;
}


