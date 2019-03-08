#ifndef HASHMAP_H
#define HASHMAP_H

#include <LinkedList.h>
#include <Queue.h>

/**
 * @class HashMap<T>
 * @brief An ADT map (dictionary) that uses a search key to identify 
 *   its values.
 * @details
 * An instance of this Map(dictionary) ADT will have 256 buckets of 
 * type linked nodes. https://en.wikipedia.org/wiki/Hash_table 
 * This Map is implemented with a hash function using a positive 
 * checksum of the key to provide an even distribution between buckets.
 * This is done by adding each characters ASCII value creating a sum indexing
 * the string value. Collision resolution is then performed via standard 
 * binary search within a bucket. For large amounts of keys the buckets will
 * fill up increasing the load factor. Once hashed, string values can be
 * added, deleted, and retreived. This map can provide the number of values
 * stored, check if a value is in the map, check if any values are in the map,
 * and clear its contents.
 */ 
const int HASHTABLE_SIZE = 256;
typedef unsigned char BYTE;
template <class T>
class HashMap
{
    private:

    int count;
    LinkedList<T> hashTable[HASHTABLE_SIZE];
    BYTE checksumHash(string);
  
    public:

    bool   isEmpty();
    int    getSize();
    T      select(string);
    bool   insert(string, T);
    bool   update(string, T);
    bool   remove(string);
    bool   hasKey(string);
    void   drop();
    bool   dump(Queue<T> *);
    HashMap();
          ~HashMap();
};

/**
 * Retrieves a value with a given search key from this map.
 *
 * @param key The search key associated with the value to be retrieved.
 * @return The value associated with the search key.
 * @throw If retrieval is not successful, throws an exception.
 */
template <class T>
T HashMap<T>::select(string key)
{
    BYTE bucket     = checksumHash(key);            // compute the bucket index
    Node<T>  *node  = hashTable[bucket].getFirst(); // we start at head of line
    int bucketCount = hashTable[bucket].getCount(); // we get the bucket count
    T   r           = T();                          // default template constructor

    for(int i=0; i < bucketCount ; i++)
    {
      if(key == node->getKey())  // if we got a match
	return(node->getData()); // return node's value 
      node = node->getNext();    // otherwise set node to next in list
    }
    // we wont get here if a match is found...
    throw std::runtime_error("No value for "+key);   
    return(r);
}

/**
 * Adds a value into this map according to it's search key.
 *
 * @param key The search key associated with value to be stored.
 * @param value The value to add to the map.
 * @return True if value was stored successfully, or false if not.
 */
template <class T>
bool HashMap<T>::insert(string key, T data)
{
    if(key == "")
        return(false);               // Invalid key is a non starter
    BYTE bucket = checksumHash(key); // Compute the bucket index.
    hashTable[bucket].add(key,data); // Add to BucketList
    this->count++;                   // bump total count
    return(true);
}


/**
 * Updates a value into this map according to it's search key.
 *
 * @param key The search key associated with value to be stored.
 * @param value The value to add to the map.
 * @return True if value was stored successfully, or false if not.
 */
template <class T>
bool HashMap<T>::update(string key, T data)
{
    BYTE bucket    = checksumHash(key);            // compute the bucket index
    Node<T > *node = hashTable[bucket].getFirst(); // we start at head of line
    int bucketCount= hashTable[bucket].getCount(); // we get the bucket count

    for(int i=0; i < bucketCount; i++)
    {
        if(key == node->getKey())
	{                          // if we got a match
	    node->setData(data);   // update the node data
	    return(true);          // return success 
	}
        node = node->getNext();    // otherwise set node to next in list
    }
    //-------------------------------------------------
    // if we get here then...
    // this is NOT the droid you are looking for :-)
    // ------------------------------------------------
    return(false);
}


/**
 * Deletes a value from this map according to it's search key.
 *
 * @param key The search key associated with the value to be removed.
 * @return True if value was removed successfully, or false if not.
 */
template <class T>
bool HashMap<T>::remove(string key)
{
    BYTE bucket    = checksumHash(key);            // compute the bucket index
    Node<T > *node = hashTable[bucket].getFirst(); // we start at head of line
    int bucketCount= hashTable[bucket].getCount(); // we get the bucket count
 
    for(int i=0; i < bucketCount; i++)
    {
        if(key == node->getKey())
	{                                   // if we got a match
	    hashTable[bucket].remove(node); // delete the node...
            this->count--;                  // decrement total count
	    return(true);                   // return success 
	}
        node = node->getNext();             // otherwise set node to next in list
    }
    //-------------------------------------------------
    // if we get here then...
    // this is NOT the droid you are looking for :-)
    // ------------------------------------------------
    return(false);
}


/**
 * hasKey() returns boolean for existance of search key in HashMap.
 *
 * @param string -- The search key.
 * @return bool  -- True if  found, or false if not.
 */
template <class T>
bool HashMap<T>::hasKey(string key)
{
    BYTE bucket    = checksumHash(key);            // compute the bucket index
    Node<T > *node = hashTable[bucket].getFirst(); // we start at head of line
    int bucketCount= hashTable[bucket].getCount(); // we get the bucket count
 
    for(int i=0; i < bucketCount; i++)
    {
        if(key == node->getKey())   // if found...
	    return(true);           // return success 
        node = node->getNext();     // otherwise set node to next in list
    }
    //-------------------------------------------------
    // if we get here then...
    // this is NOT the droid you are looking for :-)
    // ------------------------------------------------
    return(false);
}

/**
 * Removes all entries in this map.
 */
template <class T>
void HashMap<T>::drop()
{
    // initialize this stuff to zero for now...
    Node<T> *node = 0;
    Node<T> *next = 0;
    
    int   bucketCount=0;

    for( int i=0; i < HASHTABLE_SIZE; i++)    // for each bucket in hash table...
    {
        bucketCount = hashTable[i].getCount();// bucketCount is count in our line
        node  = hashTable[i].getFirst();      // we start at head of line
        while(bucketCount)
        {
	    next = node->getNext();    // get node->next before deleting    
	    hashTable[i].remove(node); // remove node from list 
	    node = next;               // and set node to next in list
            this->count--;             // decrement count of HashMap<T>
            bucketCount--;             // decrement loop control count...
	}
    }
    return;
}

/**
 * dumps a hashtable to a Queue.
 *
 * @param Queue<T> * -- pointer to supplied Queue to dump to.
 * @return bool      -- True if dump successful, or false if not.
 */
template <class T>
bool HashMap<T>::dump(Queue<T> *dataQueue)
{
    if(dataQueue == 0)
	return(false);  // bad Queue

    // initialize this stuff to zero for now...
    Node<T> *node  = 0;
    Node<T> *next  = 0;    
    int bucketCount=0;

    for( int i=0; i < HASHTABLE_SIZE; i++)    // for each bucket in hash table...
    {
        bucketCount = hashTable[i].getCount();// bucketCount is count in our line
        node  = hashTable[i].getFirst();      // we start at head of line
        while(bucketCount)
        {   //-----------------------------------
	    // just enqueue data from hashtable
	    //-----------------------------------
            dataQueue->enqueue(node->getData());
	    node = node->getNext();    // set node to next in list
            bucketCount--;             // decrement loop control count...
	}
    }
    return(true);
}    

/**
 * Checks whether this map is empty.
 * @return true if the map is empty, false if not.
 */
template <class T>
bool HashMap<T>::isEmpty()
{
    if(this->count == 0)
	return true;
    else
        return false;
}

/**
 * Gets number of items in this map.
 * @return Number of key-value pairs (elements) in this map.
 */
template <class T>
int HashMap<T>::getSize()
{
    return(this->count);
}

/**
 * This is the hash function -- implementing a positive checksum on
 * on the key string resulting in a number between 0-255
 *
 * @param  string search key
 * @return BYTE   between 0-255
 */
template <class T>
BYTE HashMap<T>::checksumHash(string key)
{
    BYTE sum=0;
    const char* k= key.c_str();
    for(int i=0; k[i]; i++)
    {
	sum += (BYTE)k[i];
    }

    return(sum);
}


/**
 * Default Constructor
 */
template <class T>
HashMap<T>::HashMap()
{
    this->count = 0;
}

/**
 * Deconstructor
 */
template <class T>
HashMap<T>::~HashMap()
{
    this->drop();    
}

#endif
