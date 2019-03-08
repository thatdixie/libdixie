#ifndef QUEUE_H
#define QUEUE_H

#include <LinkedList.h>

/**
 * @class Queue<T>
 * @brief An ADT FIFO Queue.
 * @details methods enqueue and dequeue
 */ 
template <class T>
class Queue
{
    private:

    LinkedList<T> list;
  
    public:

    bool   enqueue(T);
    T      dequeue();
    T      peek();
    bool   isEmpty();
    int    getSize();
    void   drop();
           Queue();
          ~Queue();
};
/**
 * enqueue operation -- adds to tail of list
 * @param The data to add to the Queue.
 * @return True if data was stored successfully, or false if not.
 */
template <class T>
bool Queue<T>::enqueue(T data)
{
    list.add(data);
    return(true);
}

/**
 * dequeue operation -- returns from head of list and then removes node
 * @return T -- datum.
 */
template <class T>
T Queue<T>::dequeue()
{
    T data        = T();
    Node<T>  *node=0;
    
    if(!list.isEmpty())
    {
	node = list.getFirst();
	data = node->getData();
        list.remove(node);
    }
    return(data);
}
/**
 * peek -- returns from head of list without removing node
 * @return T -- datum.
 */
template <class T>
T Queue<T>::peek()
{
    T data      = T();
    Node<T>  *node=0;
    
    if(!list.isEmpty())
    {
	node = list.getFirst();
	data = node->getData();
    }
    return(data);
}

/**
 * Checks whether this Queue is empty.
 * @return true if the Queue is empty, false if not.
 */
template <class T>
bool Queue<T>::isEmpty()
{
  if(list.getCount() == 0)
	return true;
    else
        return false;
}

/**
 * Gets number of items in this Queue.
 * @return Number of elements in this Queue.
 */
template <class T>
int Queue<T>::getSize()
{
  return(list.getCount());
}

/**
 * Removes all entries in this Queue.
 */
template <class T>
void Queue<T>::drop()
{
  while(!isEmpty())
    dequeue();  
    return;
}

/**
 * Default Constructor
 */
template <class T>
Queue<T>::Queue()
{

}

/**
 * Deconstructor
 */
template <class T>
Queue<T>::~Queue()
{
    this->drop();    
}

#endif
