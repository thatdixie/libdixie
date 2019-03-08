#include <PhoneContacts.h>

/**
 * Adds a record into this map according to it's search key.
 *
 * @param key The search key associated with record to be stored.
 * @param record The record to add to the map.
 * @return True if record was stored successfully, or false if not.
 */
bool PhoneContacts::insert(string key, PHONE_CONTACT record)
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
bool PhoneContacts::update(string key, PHONE_CONTACT record)
{
    return(hashMap->update(key, record));
}

/**
 * Retrieves a PHONE_CONTACT record with a given search key from this map.
 *
 * @param key The search key associated with the record to be retrieved.
 * @return The record associated with the search key.
 * @throw If retrieval is not successful, throws an exception.
 */
PhoneContacts::PHONE_CONTACT PhoneContacts::select(string key)
{
    return (hashMap->select(key));
}

/**
 * Deletes a record from this map according to it's search key.
 *
 * @param key The search key associated with the record to be removed.
 * @return True if record was removed successfully, or false if not.
 */
bool PhoneContacts::remove(string key)
{
    return(hashMap->remove(key));
}

/**
 * Removes all entries in this map.
 */
void PhoneContacts::drop()
{
    hashMap->drop();
    return;
}

/**
 * dumps a hashtable to a Queue.
 *
 * @param Queue<T> * -- pointer to supplied Queue to dump to.
 * @return bool      -- True if dump successful, or false if not.
 */
bool PhoneContacts::dump( Queue<PhoneContacts::PHONE_CONTACT> *q)
{
    return(hashMap->dump(q));
}



/**
 * Checks whether this map is empty.
 * @return true if the map is empty, false if not.
 */
bool PhoneContacts::isEmpty()
{
    return(hashMap->isEmpty());
}


/**
 * Gets number of items in this map.
 * @return Number of key-record pairs (elements) in this map.
 */
int PhoneContacts::getSize()
{
    return(hashMap->getSize());
}



/**
 * Default Constructor
 */
PhoneContacts::PhoneContacts()
{
    hashMap = new HashMap<PHONE_CONTACT>;
}


/**
 * Deconstructor
 */
PhoneContacts::~PhoneContacts()
{
    hashMap->drop();
}

