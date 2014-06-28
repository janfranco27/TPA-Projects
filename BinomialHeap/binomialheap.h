#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include<list>
#include<iterator>
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

    T getMinimumKey()
    {
        if(minValue == headList.end())
        {
            HeapIterator it = headList.begin();
            minValue = headList.begin();
            for(;it != headList.end(); ++it)
            {
                if((*minValue)->key > (*it)->key)
                    minValue = it;
            }
            return (*minValue)->key;
        }
        return (*minValue)->key;
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
                if ( (*current)->key <= (*next)->key )
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

        delete currentValue;
        BinomialHeap<T> minSonsHeap (minSonsList);

        binomialHeapUnion(minSonsHeap);
        getMinimumKey();
    }

    HeapNode<T>* findNode(HeapNode<T> &nodeToSearch)
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
            if(*current == nodeToSearch)
                return current;
            else if(*current < nodeToSearch)
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

    void decreaseKey(T previous, T newKey)
    {
        HeapNode<T> previousNode(previous);
        HeapNode<T>* node = findNode(previousNode);
        if(node)
        {
            node->key = newKey;
            HeapNode<T>* y = node;
            HeapNode<T>* z = node->parent;
            while(z && y->key < z->key)
            {
                T tmp = y->key;
                y->key = z->key;
                z->key = tmp;
                y = z;
                z = y->parent;
            }
        }
        minValue = headList.end();
        getMinimumKey();
    }

    void deleteNode(T data, T minusInfinity)
    {
        decreaseKey(data, minusInfinity);
        extractMin();
    }
};

#endif // BINOMIALHEAP_H
