#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include<list>
#include<vector>
#include<iterator>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<FibonacciNode.h>

using namespace  std;

template <class T>
class FibonacciHeap
{
    public:
    typedef typename list<FibonacciNode<T>* >::iterator HeapIterator;
    list<FibonacciNode<T>* > headList;
    HeapIterator minValue;
    int numberOfNodes;

    FibonacciHeap ()
    {
        minValue = headList.end();
        numberOfNodes = 0;
    }

    T getMinimumKey()
    {
        return (*minValue)->key;
    }

    void insert (T data)
    {
        FibonacciNode<T> *node = new FibonacciNode<T> (data);
        headList.push_front(node);
        if(minValue == headList.end() || node->key < getMinimumKey())
        {
            //begin porq se ahce push_front
            minValue = headList.begin();
        }
        numberOfNodes++;
    }

    void fibonacciHeapUnion (FibonacciHeap<T> &h_2)
    {
        headList.splice(headList.end(),h_2.headList);
        if( (minValue == headList.end()) || (h_2.minValue != h_2.headList.end() && h_2.getMinimumKey() < getMinimumKey()) )
        {
            minValue = h_2.minValue;
        }
        numberOfNodes += h_2.numberOfNodes;
    }

    void extractMin()
    {
        HeapIterator z = minValue;
        if(z != headList.end())
        {
            HeapIterator minSons = (*z)->sons.begin();
            for (; minSons != (*z)->sons.end(); ++minSons)
            {
                headList.push_back(*minSons);
                (*minSons)->parent = 0;
            }
            headList.erase(z);
            if(headList.empty())
                minValue = headList.end();
            else
            {
                minValue = headList.begin();
                consolidate();
            }

            numberOfNodes--;
        }
    }

    void fibonacciLink(FibonacciNode<T> *h1, FibonacciNode<T> *h2)
    {
        headList.remove(h1);
        h2->sons.push_front(h1);
        h1->parent = h2;
        h2->degree++;
        h1->marked = false;
    }

    void consolidate()
    {
        HeapIterator it = headList.begin();
        //maxGrado = 2*log_2 (n)
        int maxGrado = 2 * log10(numberOfNodes)/log10(2);

        vector<FibonacciNode<T>* > A;
        for (int i = 0; i < maxGrado + 1; i++)
            A.push_back(NULL);

        HeapIterator w = headList.begin();
        HeapIterator tmp = headList.begin();

        for(; w != headList.end(); )
        {
            tmp++;
            FibonacciNode<T> *x = *w;
            int d = x->degree;
            while (A[d])
            {
                FibonacciNode<T> *y = A[d];
                if(x->key > y->key)
                {
                    FibonacciNode<T> *tmp = y;
                    y = x;
                    x = tmp;
                }
                fibonacciLink(y, x);
                A[d] = 0;
                d++;
            }
            A[d] = x;
            w = tmp;

        }
        minValue = headList.begin();

        HeapIterator min = headList.begin();
        for( ; min != headList.end(); ++min)
            if((*min)->key < (*minValue)->key)
                minValue = min;

    }


    FibonacciNode<T>* findNode(FibonacciNode<T> &nodeToSearch)
    {
        list<FibonacciNode<T>* > queue;
        HeapIterator it = headList.begin();

        for(; it != headList.end(); ++it)
        {
            FibonacciNode<T> *t = *it;
            queue.push_back(t);
        }

        while(!queue.empty())
        {
            FibonacciNode<T>* current = queue.front();
            queue.erase(queue.begin());
            if(*current == nodeToSearch)
                return current;
            else if(*current < nodeToSearch)
            {
                HeapIterator sons = current->sons.begin();
                for (; sons != current->sons.end(); ++sons)
                {
                    FibonacciNode<T> *t = *sons;
                    queue.push_back(t);
                }
            }
        }
        return NULL;
    }

    void decreaseKey(T previous, T newKey)
    {
        FibonacciNode<T> previousNode(previous);
        FibonacciNode<T>* node = findNode(previousNode);
        if(node)
        {
            node->key = newKey;
            FibonacciNode<T> *y = node->parent;
            if(y && node->key < y->key)
            {
                cut(node,y);
                cascadingCut(y);
            }
            /*if(node->key < (*minValue)->key)
                minValue = node;
            */
            HeapIterator min = headList.begin();
            for( ; min != headList.end(); ++min)
                if((*min)->key < (*minValue)->key)
                    minValue = min;
        }
    }

    void cut(FibonacciNode<T> *x, FibonacciNode<T> *y)
    {
        y->sons.remove(x);
        y->degree--;
        headList.push_front(x);
        x->parent = NULL;
        x->marked = false;
    }

    void cascadingCut(FibonacciNode<T> *y)
    {
        FibonacciNode<T> *z = y->parent;
        if(z)
        {
            if(!y->marked)
                y->marked = true;
            else
            {
                cut(y,z);
                cascadingCut(z);
            }
        }
    }

    void deleteNode(T data, T minusInfinity)
       {
           decreaseKey(data, minusInfinity);
           extractMin();
       }
};

#endif // FIBONACCIHEAP_H
