#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <Node.h>

/**
 * @class LinkedList
 * @brief An ADT Linked List using Node<T>.
 */
template <class T>
class LinkedList
{
    private:

    Node<T> *head;
    Node<T> *tail;
    int     count;  
  
    public:

    bool     isEmpty();
    int      getCount();
    void     add(T );
    void     add(string, T );
    void     insert(int, T );
    void     remove(Node<T> *);
    Node<T> *getNode(int); 
    Node<T> *getFirst();
    Node<T> *getLast();
             LinkedList();
};

/**
 * Adds data to new Node and link to list.
 * @param T data.
 * @return void
 */
template <class T>
void LinkedList<T>::add(T data)
{
    add("", data);
}
/**
 * Adds data to new Node and link to list.
 * @param string 
 * @param T data.
 * @return void
 */
template <class T>
void LinkedList<T>::add(string key, T data)
{
    if(isEmpty())
    {
        head = new Node<T>; // was empty so create new Node
        head->setData(data);// set data
	head->setKey(key);  // set key
        tail = head;        // it's now first and last
        head->setPrevious(0);
	head->setNext(0);
    }
    else
    {
        Node<T> *node = new Node<T>;// create new Node
        node->setData(data);        // set data
	node->setKey(key);          // set key
        node->setNext(0);           // it's now the last one
        node->setPrevious(tail);    // previous is current tail
        tail->setNext(node);        // current tail->next is now new Node
        tail = node;                // now tail is new Node 
    }
    this->count++;
}

/**
  * Insert data into List at index.
  * @param int index
  * @param T data
  * @return void.
  */
template <class T>
void LinkedList<T>::insert(int index, T data)
{
    if( index < 0 || index >= this->count) // if offset is out of bounds (less than 0 or >=count) then
        add(data);                         // this becomes a regular add()...   
    else
    {                                      // else we are going to insert a new Node
        Node<T> *p = getFirst();           // at the offset and need to start at the head
	for(int i=0; i <index; i++)        // so, we're gonna find the  
	    p = p->getNext();              // spot in list to insert a node (a current node is there )
        Node<T> *n = new Node<T>;          // after we found the spot -- create new Node<T>
	n->setData(data);                  // set data/payload
	n->setKey("");                     // set key to empty 
        n->setNext(p);                     // set next pointer to node being pushed down 
        n->setPrevious(p->getPrevious());  // set previous pointer to previous poiner of node being pushed down
        if(index !=0)                      // if offset is not the new front of list then...
            p->getPrevious()->setNext(n);  // set next pointer of node ahead of new node to new node        
        else                               // otherwise...
	    head =n;                       // set head pointer to new node at front of list
        p->setPrevious(n);                 // set previous pointer of node being pushed down to new node
        this->count++;                     // bump the node count for this list -- and we're done :-)  
    }
}

/**
  * Removes a Node from List.
  * @param Node<T> *
  * @return void.
  */
template <class T>
void LinkedList<T>::remove(Node<T> * node)
{
    if(node == 0 || this->count == 0)
        return;
    Node<T> *p = node->getPrevious();
    Node<T> *n = node->getNext();
    if(this->head == node)// if first then re-position head...
      this->head=n;
    if(this->tail == node)// if last then re-position tail...
      this->tail=p;
    if(p !=0)             // if there is a previous then...
        p->setNext(n);    // previous->next = next node
    if(n !=0)             // if there is a next then...
        n->setPrevious(p);// next->previous = previous node
    delete node;          // this one is removed
    this->count--;        // decrement node count
    return;
}


/**
  * Get Node at index in List.
  * @param int index
  * @return Node<T> *
  */
template <class T>
Node<T> *LinkedList<T>::getNode(int index)
{
    if( index < 0 || index >= this->count) // if offset is out of bounds (less than 0 or >=count) then
        return(0);                         // return null pointer...
    else
    {
        Node<T> *p = getFirst();           // at the offset and need to start at the head
	for(int i=0; i <index; i++)        // so, we're gonna find the  
	    p = p->getNext();              // spot in list to get our node...
        return(p);                         // we found Node at index :-)
    }
}

/**
 * Get first Node in list.
 * @return The poiner to first Node in list.
 */
template <class T>
Node<T> *LinkedList<T>::getFirst()
{
    return(this->head);
}

/**
 * Get last Node in list.
 * @return The poiner to first Node in list.
 */
template <class T>
Node<T> *LinkedList<T>::getLast()
{
    return(this->tail);
}

/**
 * Checks whether this list is empty.
 * @return True if the list is empty, false if not.
 */
template <class T>
bool LinkedList<T>::isEmpty()
{
    if(!this->count)
	return(true);
    else
        return(false);
}

/**
 * Gets number of items in this list.
 * @return Number of items in list.
 */
template <class T>
int LinkedList<T>::getCount()
{
  return(this->count);
}

/**
 * Default Constructor
 */
template <class T>
LinkedList<T>::LinkedList()
{
    this->head = 0;
    this->tail = 0;
    this->count= 0;
}

#endif
