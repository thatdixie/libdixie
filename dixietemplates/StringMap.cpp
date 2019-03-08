#include "StringMap.h"

/**
 * Adds a value into this map according to it's search key.
 *
 * @param key The search key associated with value to be stored.
 * @param value The value to add to the map.
 * @return True if value was stored successfully, or false if not.
 */
bool StringMap::insert(string key, string value)
{
    return(hashMap->insert(key, value));
}

/**
 * Updates a value into this map according to it's search key.
 *
 * @param key The search key associated with value to be stored.
 * @param value The value to update to the map.
 * @return True if value was stored successfully, or false if not.
 */
bool StringMap::update(string key, string value)
{
    return(hashMap->update(key, value));
}

/**
 * Retrieves a value with a given search key from this map.
 *
 * @param key The search key associated with the value to be retrieved.
 * @return The value associated with the search key.
 * @throw If retrieval is not successful, throws an exception.
 */
string StringMap::select(string key)
{
    return (hashMap->select(key));
}

/**
 * Deletes a value from this map according to it's search key.
 *
 * @param key The search key associated with the value to be removed.
 * @return True if value was removed successfully, or false if not.
 */
bool StringMap::remove(string key)
{
    return(hashMap->remove(key));
}

/**
 * Removes all entries in this map.
 */
void StringMap::drop()
{
    hashMap->drop();
    return;
}

/**
 * Checks whether this map is empty.
 * @return true if the map is empty, false if not.
 */
bool StringMap::isEmpty()
{
    return(hashMap->isEmpty());
}


/**
 * Gets number of items in this map.
 * @return Number of key-value pairs (elements) in this map.
 */
int StringMap::getSize()
{
    return(hashMap->getSize());
}


/**
 * Default Constructor
 */
StringMap::StringMap()
{
    hashMap = new HashMap<string>;
}


/**
 * Deconstructor
 */
StringMap::~StringMap()
{
    hashMap->drop();
}

