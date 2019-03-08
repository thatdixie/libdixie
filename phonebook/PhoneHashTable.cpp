#include "PhoneHashTable.h"

/**
 * Adds a record into this map according to it's search key.
 *
 * @param key The search key associated with record to be stored.
 * @param record The record to add to the map.
 * @return True if record was stored successfully, or false if not.
 */
bool PhoneHashTable::insert(string key, PhoneContact record)
{
    return(hashMap->insert(key, record));
}

/**
 * Updates a record into this map according to it's search key.
 *
 * @param key The search key associated with record to be stored.
 * @param record The record to update to the map.
 * @return True if record was stored successfully, or false if not.
 */
bool PhoneHashTable::update(string key, PhoneContact record)
{
    return(hashMap->update(key, record));
}

/**
 * Retrieves a PhoneContact record with a given search key from this map.
 *
 * @param key The search key associated with the record to be retrieved.
 * @return The record associated with the search key.
 * @throw If retrieval is not successful, throws an exception.
 */
PhoneContact PhoneHashTable::select(string key)
{
    return (hashMap->select(key));
}

/**
 * Deletes a record from this map according to it's search key.
 *
 * @param key The search key associated with the record to be removed.
 * @return True if record was removed successfully, or false if not.
 */
bool PhoneHashTable::remove(string key)
{
    return(hashMap->remove(key));
}


/**
 * Checks existance for a given search key in this map.
 *
 * @param string --  The search key.
 * @return bool  --  True if found, or false if not.
 */
bool PhoneHashTable::hasKey(string key)
{
    return(hashMap->hasKey(key));
}


/**
 * Removes all entries in this map.
 */
void PhoneHashTable::drop()
{
    hashMap->drop();
    return;
}

/**
 * Dumps a hashtable to a Queue.
 *
 * @param Queue<T> * -- pointer to supplied Queue to dump to.
 * @return bool      -- True if dump successful, or false if not.
 */
bool PhoneHashTable::dump(Queue<PhoneContact> *q)
{
    return(hashMap->dump(q));
}

/**
 * Checks whether this map is empty.
 * @return true if the map is empty, false if not.
 */
bool PhoneHashTable::isEmpty()
{
    return(hashMap->isEmpty());
}


/**
 * Gets number of items in this map.
 * @return Number of key-record pairs (elements) in this map.
 */
int PhoneHashTable::getSize()
{
    return(hashMap->getSize());
}


/**
 * Default Constructor
 */
PhoneHashTable::PhoneHashTable()
{
    hashMap = new HashMap<PhoneContact>;
}


/**
 * Deconstructor
 */
PhoneHashTable::~PhoneHashTable()
{
    hashMap->drop();
}

