#ifndef STACK_H
#define STACK_H

#include <LinkedList.h>

/**
 * @class Stack<T>
 * @brief An ADT LIFO List.
 * @details methods push, pop and peek
 */ 
template <class T>
class Stack
{
    private:

    LinkedList<T> list;
  
    public:

    bool   push(T);
    T      pop();
    T      peek();
    bool   isEmpty();
    int    getSize();
    void   drop();
           Stack();
          ~Stack();
};

/**
 * push operation -- adds to top of stack
 * @param The data to push to the Stack.
 * @return True if data was stored successfully, or false if not.
 */
template <class T>
bool Stack<T>::push(T data)
{
    list.add(data);
    return(true);
}

/**
 * pop operation -- returns from tail of list and then removes node
 * @return T -- datum.
 */
template <class T>
T Stack<T>::pop()
{
    T data        = T();
    Node<T>  *node=0;
    
    if(!list.isEmpty())
    {
	node = list.getLast();
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
T Stack<T>::peek()
{
    T data        = T();
    Node<T>  *node=0;
    
    if(!list.isEmpty())
    {
	node  = list.getLast();
	data  = node->getData();
    }
    return(data);
}

/**
 * Checks whether this Stack is empty.
 * @return true if the Stack is empty, false if not.
 */
template <class T>
bool Stack<T>::isEmpty()
{
    if(list.getCount() == 0)
        return true;
    else
        return false;
}

/**
 * Gets number of items in this Stack.
 * @return Number of elements in this Stack.
 */
template <class T>
int Stack<T>::getSize()
{
    return(list.getCount());
}

/**
 * Removes all entries in this Stack.
 */
template <class T>
void Stack<T>::drop()
{
    while(!isEmpty())
        pop();  

    return;
}

/**
 * Default Constructor
 */
template <class T>
Stack<T>::Stack()
{

}

/**
 * Deconstructor
 */
template <class T>
Stack<T>::~Stack()
{
    this->drop();    
}

#endif
