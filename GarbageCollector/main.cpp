#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <thread>
#include <binomialheap.h>
#include <vector>
#include <chrono>


using namespace std;

static BinomialHeap<void *> garbageCollector;


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

void* crearNodo(void* address, int size)
{
    char* block = (char *)malloc(size);
    memcpy(block, address, size);

    garbageCollector.insert(block,size);
    return block;
}

void assign(void ** destiny, void ** source)
{
    HeapNode<void*>* resultDestiny = garbageCollector.findNode(destiny);
    if(resultDestiny)
    {
        garbageCollector.decreaseKey(destiny, resultDestiny->pointedBy - 1);
        if(resultDestiny->pointedBy == 0)
        {
            garbageCollector.extractMin();
        }
    }
    HeapNode<void*>* resultSource = garbageCollector.findNode(source);
    if(resultSource)
    {
        garbageCollector.increaseKey(resultSource, 1);
    }
    destiny = source;

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


int main()
{

    Persona A(1,1,"aa");
    Persona B(2,2,"bb");
    Persona* q = (Persona *)crearNodo(&A,sizeof(A));
    Persona* r = (Persona *)crearNodo(&B,sizeof(B));

    Persona* a;

    assign ((void **) &a,(void **) &q);
    assign ((void **) &a,(void **) &r);
    assign ((void **) &q,(void **) &r);
    //std::thread t (run);
    //t.join();

    return 0;
}
