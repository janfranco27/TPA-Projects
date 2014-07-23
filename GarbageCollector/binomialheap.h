#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include<list>
#include<iterator>
#include<stdlib.h>
#include<heapnode.h>

template <class Iter, class Incr>
void safe_advance(Iter& curr, const Iter& end, Incr n)
{
  size_t remaining(std::distance(curr, end));
  if (remaining < n)
  {
    n = remaining;
  }
  std::advance(curr, n);
}

template <class T>
class BinomialHeap
{
    public:

    typedef typename list <HeapNode<T>* >::iterator HeapIterator;
    list <HeapNode<T>* > headList;
    HeapIterator minValue;

    BinomialHeap()
    {
        minValue = headList.end();
    }

    BinomialHeap(list<HeapNode<T>* > &list)
    {
        minValue = headList.end();
        headList = list;
    }

    int getMinimumKey()
    {
        if(minValue == headList.end())
        {
            HeapIterator it = headList.begin();
            minValue = headList.begin();
            for(;it != headList.end(); ++it)
            {
                if((*minValue)->pointedBy > (*it)->pointedBy)
                    minValue = it;
            }
            return (*minValue)->pointedBy;
        }
        return (*minValue)->pointedBy;
    }

    void addHeapNode (HeapNode<T> *node)
    {
        headList.push_front(node);
    }

    void binomialLink(HeapNode<T> *h1, HeapNode<T> *h2)
    {
        h1->parent = h2;
        h2->sons.push_front(h1);
        h2->degree++;
    }

    void binomialHeapMerge(BinomialHeap<T> &h_2)
    {
        //une dos heaps en uno solo, ordenando los elementos en las cabezas por grado
        //de manera creciente
        list<HeapNode<T>* > tmpList;
        HeapIterator firstHeapIt = headList.begin();
        HeapIterator secondHeapIt = h_2.headList.begin();

        while (firstHeapIt != headList.end() && secondHeapIt != h_2.headList.end())
        {
            if((*firstHeapIt)->degree < (*secondHeapIt)->degree)
            {
                tmpList.push_back(*firstHeapIt);
                firstHeapIt++;
            }
            else
            {
                tmpList.push_back(*secondHeapIt);
                secondHeapIt++;
            }
        }

        while (secondHeapIt != h_2.headList.end())
        {
            tmpList.push_back(*secondHeapIt);
            secondHeapIt++;
        }

        while (firstHeapIt != headList.end())
        {
            tmpList.push_back(*firstHeapIt);
            firstHeapIt++;
        }

        headList.clear();
        h_2.headList.clear();
        headList = tmpList;
    }


    void binomialHeapUnion(BinomialHeap<T> &h_2)
    {
        binomialHeapMerge(h_2);
        list<HeapNode<T>* > tmpList = headList;
        HeapIterator current = tmpList.begin();
        if(current == tmpList.end())
            return;
        HeapIterator prev = tmpList.end();

        HeapIterator next = current;
        safe_advance (next,tmpList.end(),1);

        HeapIterator next_next = current;
        safe_advance (next_next,tmpList.end(),2);

        while (next != tmpList.end())
        {
            if( ((*current)->degree != (*next)->degree) ||
                (next_next != tmpList.end() && (*next_next)->degree == (*current)->degree ) )
            {
                prev = current;
                current = next;
            }
            else
            {
                if ( (*current)->pointedBy <= (*next)->pointedBy )
                {
                    HeapNode<T> *nextValue = *next;

                    tmpList.erase(next);
                    binomialLink(nextValue, *current);
                    next = current;

                }
                else
                {
                    HeapNode<T> *currentValue = *current;

                    current = tmpList.erase(current);

                    binomialLink(currentValue, *next);

                    current = next;
                }

            }
            safe_advance(next,tmpList.end(),1);
            safe_advance(next_next,tmpList.end(),1);
        }
        headList.clear();
        headList = tmpList;
    }

    void insert (T data)
    {
        HeapNode<T> *node = new HeapNode<T> (data);
        BinomialHeap<T> h_2;
        h_2.addHeapNode (node);
        binomialHeapUnion(h_2);
    }

    void insert (T data, int size)
    {
        HeapNode<T> *node = new HeapNode<T> (data,size);
        BinomialHeap<T> h_2;
        h_2.addHeapNode (node);
        binomialHeapUnion(h_2);
    }

    void extractMin()
    {
        if(minValue == headList.end()) getMinimumKey();
        HeapIterator current = minValue;
        HeapNode<T>* currentValue = *current;
        current = headList.erase(current);
        minValue = headList.end();

        list<HeapNode<T>* > minSonsList;
        HeapIterator sonsIt = currentValue->sons.begin();
        for (; sonsIt != currentValue->sons.end(); ++sonsIt)
        {
            (*sonsIt)->parent = 0;
            minSonsList.push_front(*sonsIt);
        }

        free (currentValue->address);
        delete currentValue;
        BinomialHeap<T> minSonsHeap (minSonsList);

        binomialHeapUnion(minSonsHeap);
        getMinimumKey();
    }

    HeapNode<T>* findNode(T nodeToSearch)
    {
        list<HeapNode<T>* > queue;
        HeapIterator it = headList.begin();

        for(; it != headList.end(); ++it)
        {
            HeapNode<T> *t = *it;
            queue.push_back(t);
        }

        while(!queue.empty())
        {
            HeapNode<T>* current = queue.front();
            queue.erase(queue.begin());
            if(current->address == nodeToSearch)
                return current;
            else
            {
                HeapIterator sons = current->sons.begin();
                for (; sons != current->sons.end(); ++sons)
                {
                    HeapNode<T> *t = *sons;
                    queue.push_back(t);
                }
            }
        }
        return NULL;
    }

    void decreaseKey(T previous, int newKey)
    {
        HeapNode<T>* node = findNode(previous);
        if(node)
        {
            node->pointedBy = newKey;
            HeapNode<T>* y = node;
            HeapNode<T>* z = node->parent;
            while(z && y->pointedBy < z->pointedBy)
            {
                T tmp = y->address;
                int tmpSize = y->size;
                int tmpPointed = y->pointedBy;

                y->address = z->address;
                y->size = z->size;
                y->pointedBy = z->pointedBy;

                z->address = tmp;
                z->size = tmpSize;
                z->pointedBy = tmpPointed;

                y = z;
                z = y->parent;
            }
        }
        minValue = headList.end();
        getMinimumKey();
    }

    void increaseKey(HeapNode<T>* node, int valueToAdd)
    {
        node->pointedBy += valueToAdd;
        HeapNode<T>* z = node;
        HeapNode<T>* y = z;

        HeapIterator sons = z->sons.begin();
        while(sons != z->sons.end())
        {
            int min = node->pointedBy;
            for(; sons != z->sons.end(); sons++)
            {
                if( (*sons)->pointedBy < min )
                {
                    min = (*sons)->pointedBy;
                    y = (*sons);
                }
            }

            if (z == y) break;
            T tmp = y->address;
            int tmpSize = y->size;
            int tmpPointed = y->pointedBy;

            y->address = z->address;
            y->size = z->size;
            y->pointedBy = z->pointedBy;

            z->address = tmp;
            z->size = tmpSize;
            z->pointedBy = tmpPointed;

            z = y;
            sons = z->sons.begin();
        }
    }


    void deleteNode(T data, int minusInfinity)
    {
        decreaseKey(data, minusInfinity);
        extractMin();
    }
};

#endif // BINOMIALHEAP_H
