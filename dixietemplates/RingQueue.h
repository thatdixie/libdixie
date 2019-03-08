#ifndef RINGQUEUE_H
#define RINGQUEUE_H

#include <Queue.h>

/**
 * @class RingQueue<T>
 * @brief An ADT Circular Queue.
 * @details methods add and getNext
 */ 
template <class T>
class RingQueue
{
    private:

    Queue<T> queue;
  
    public:

    bool   add(T);
    T      getNext();
    T      peek();
    bool   isEmpty();
    int    getSize();
    void   drop();
           RingQueue();
          ~RingQueue();
};
/**
 * add operation -- adds to tail of Queue
 * @param The data to add to the Queue.
 * @return True if data was stored successfully, or false if not.
 */
template <class T>
bool RingQueue<T>::add(T data)
{
    queue.enqueue(data);
    return(true);
}

/**
 * getNext operation -- returns from head of Queue 
 *                      then removes node 
 *                      and adds to to tail of Queue 
 * @return T -- datum.
 */
template <class T>
T RingQueue<T>::getNext()
{
    T data = T();

    if(!queue.isEmpty())
    {
	data= queue.dequeue();
        queue.enqueue(data);
    }
    return(data);
}
/**
 * peek -- returns from head of queue without removing node
 * @return T -- datum.
 */
template <class T>
T RingQueue<T>::peek()
{
    return(queue.peek());
}

/**
 * Checks whether this Queue is empty.
 * @return true if the Queue is empty, false if not.
 */
template <class T>
bool RingQueue<T>::isEmpty()
{
    return(queue.isEmpty());
}

/**
 * Gets number of items in this Queue.
 * @return Number of elements in this Queue.
 */
template <class T>
int RingQueue<T>::getSize()
{
    return(queue.getSize());
}

/**
 * Removes all entries in this Queue.
 */
template <class T>
void RingQueue<T>::drop()
{
    while(!queue.isEmpty())
        queue.dequeue();  
    return;
}

/**
 * Default Constructor
 */
template <class T>
RingQueue<T>::RingQueue()
{

}

/**
 * Deconstructor
 */
template <class T>
RingQueue<T>::~RingQueue()
{
    queue.drop();    
}

#endif
