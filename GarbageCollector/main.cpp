#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <thread>
#include <binomialheap.h>
#include <vector>
#include <chrono>


using namespace std;


class Persona
{
public:
    int dni;
    int age;
    char* name;
    Persona(){}
    Persona(int n, int a, char* na)
    {
        dni = n;
        age = a;
        name = na;
    }
};

template<class T>
void* crearNodo(void* address, int size, BinomialHeap<T> &garbageCollector)
{
    char* block = (char *)malloc(size);
    memcpy(block, address, size);

    garbageCollector.insert(block,size);
    return block;
}

template<class T>
void assign(void **destiny, void **source, BinomialHeap<T> &garbageCollector)
{
    HeapNode<T>* resultDestiny = garbageCollector.findNode(*destiny);
    if(resultDestiny)
    {
        garbageCollector.decreaseKey(*destiny, resultDestiny->pointedBy - 1);
        if(resultDestiny->pointedBy == 0)
        {
            garbageCollector.extractMin();
        }
    }
    HeapNode<T>* resultSource = garbageCollector.findNode(*source);
    if(resultSource)
    {
        garbageCollector.increaseKey(resultSource, 1);
    }
    *destiny = *source;

}

/*
void run()
{
    while (true)
    {
        std::chrono::milliseconds dura( 10000 );
        std::this_thread::sleep_for( dura );
        cout << "Waited\n";
        if(garbageCollector.getMinimumKey() == 0)
            garbageCollector.extractMin();
    }
}
*/
#define size 100000
int main()
{

    BinomialHeap <void*> garbageCollector;

    Persona A(1,1,"aa");

    Persona* people [size];
    for(int i = 0; i < size; i++)
    {
        people[i] = (Persona *)crearNodo(&A,sizeof(A), garbageCollector);

        //assign((void **)&people[i],(void **) &p, garbageCollector);
    }

    //std::thread t (run);
    //t.join();
    cout<<garbageCollector.getMinimumKey()<<endl;
    cout<<"here";
    return 0;
}


