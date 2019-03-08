#ifndef NODE_H
#define NODE_H

/**
 * @class Node
 * @brief An ADT for an object that may be used in a linked list
 * @details
 * Node class will contain a previous pointer and and next pointer 
 * and a template container for it's payload.
 */ 
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <cassert>
using namespace std;
template <class T>
class Node
{
    private:

    T        data;
    string   key;
    Node<T>  *next;
    Node<T>  *previous;

    public:

    T      getData();
    void   setData(T);
    string getKey();
    void   setKey(string);
    Node  *getPrevious();
    Node  *getNext();
    void   setPrevious(Node *);
    void   setNext(Node *);
    Node();  
};

/**
 * Gets Data from node .
 * @return <T>
 */
template <class T>
T Node<T>::getData()
{
    return (this->data);
}

/**
 * Sets Data in Node.
 * @param <T>
 */
template <class T>
void Node<T>::setData(T data)
{
    this->data = data;
}

/**
 * Gets key from node .
 * Note: Keys are only useful when used in hash maps 
 * @return string
 */
template <class T>
string Node<T>::getKey()
{
    return (this->key);
}

/**
 * Sets key in Node.
 * Note: Keys are only useful when used in hash maps 
 * @param string
 */
template <class T>
void Node<T>::setKey(string key)
{
    this->key = key;
}

/**
 * Gets pointer to previous Node in a list.
 * @return Node *
 */
template <class T>
Node<T> *Node<T>::getPrevious()
{
    return(this->previous);
}

/**
 * Gets pointer to next Node in a list.
 * @return Node *
 */
template <class T>
Node<T> *Node<T>::getNext()
{
    return(this->next);
}
   
/**
 * Sets pointer to previous Node in a list.
 * @param  Node *
 * @return void
 */
template <class T>
void Node<T>::setPrevious(Node *previous)
{
    this->previous = previous;
}

/**
 * Sets pointer to next Node in a list.
 * @param  Node *
 * @return void
 */
template <class T>
void Node<T>::setNext(Node *next)
{
    this->next = next;
}

/**
 * Default Constructor
 */
template <class T>
Node<T>::Node()
{
    this->previous=0;
    this->next    =0;
    this->key     ="";
}

#endif
