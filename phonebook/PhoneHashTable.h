#ifndef PHONEHASHTABLE_H
#define PHONEHASHTABLE_H

#include <HashMap.h>
#include "PhoneContact.h"

using namespace std;

/**
 * @class PhoneHashTable
 * @brief A map (dictionary) that uses a search key to identify 
 *        PhoneContact records.
 * @details
 * This implementation delegates to class HashMap using <PhoneContact> for data.
 * See HashMap.h for implementation details
 */ 
class PhoneHashTable
{
     private:
    //-------------------------------------------------
    // This is the HashMap of PhoneContact records.
    //-------------------------------------------------
    HashMap<PhoneContact> *hashMap;
  
    public:

  /**
   * Retrieves a record with a given search key from this map.
   * @post If retrieval is successful, record is returned.
   * @param key The search key associated with the record to be retrieved.
   * @return The record associated with the search key.
   * @throw If retrieval is not successful, throws an exception.
   */
  PhoneContact select(string key);

  /**
   * Adds a record into this map according to it's search key.
   * @pre The key to the new record differs from all other search keys in 
   *   this map.
   * @post If store is successful, the record is in proper position in 
   *   this map.
   * @param key The search key associated with record to be stored.
   * @param record The record to add to the map.
   * @return True if record was stored successfully, or false if not.
   */
   bool insert(string key, PhoneContact record);

  /**
   * Updates a record into this map according to it's search key.
   * @pre The key to the new record differs from all other search keys in 
   *   this map.
   * @post If store is successful, the record is in proper position in 
   *   this map.
   * @param key The search key associated with record to be stored.
   * @param record The record to add to the map.
   * @return True if record was stored successfully, or false if not.
   */
   bool update(string key, PhoneContact record);

  /**
   * Removes a record from this map according to it's search key.
   * @post If the record whose search key equals key existed in this map, 
   *   record was removed.
   * @param key The search key associated with the record to be removed.
   * @return True if record was removed successfully, or false if not.
   */
   bool remove(string key);

 /**
  * Checks existance for a given search key in this map.
  *
  * @param string --  The search key.
  * @return bool  --  True if found, or false if not.
  */
  bool hasKey(string);

  /**
   * Removes all entries in this map.
   */
   void drop();

  /**
   * Dumps a hashtable to a Queue.
   *
   * @param Queue<T> * -- pointer to supplied Queue to dump to.
   * @return bool      -- True if dump successful, or false if not.
   */
   bool   dump(Queue<PhoneContact> *);
    
  /**
   * Checks whether this map is empty.
   * @return True if the map is empty, false if not.
   */
   bool isEmpty();

  /**
   * Gets number of items in this map.
   * @return Number of key-record pairs (elements) in this map.
   */
   int getSize();

   /**
   * Default Constructor
   */
   PhoneHashTable();
   
  /**
   * Deconstructor
   */
   ~PhoneHashTable();
};

#endif


  
