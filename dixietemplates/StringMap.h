#ifndef STRINGMAP_H
#define STRINGMAP_H

#include <HashMap.h>

using namespace std;

/**
 * @class StringMap
 * @brief An ADT map (dictionary) that uses a search key to identify 
 *   its values.
 * @details
 * This implementation delegates to class HashMap using <string> for data.
 * See HashMap.h for implementation details
 */ 
class StringMap
{
    private:

    HashMap<string> *hashMap;
  
    public:

  /**
   * Retrieves a value with a given search key from this map.
   * @post If retrieval is successful, value is returned.
   * @param key The search key associated with the value to be retrieved.
   * @return The value associated with the search key.
   * @throw If retrieval is not successful, throws an exception.
   */
  string select(string key);

  /**
   * Adds a value into this map according to it's search key.
   * @pre The key to the new value differs from all other search keys in 
   *   this map.
   * @post If store is successful, the value is in proper position in 
   *   this map.
   * @param key The search key associated with value to be stored.
   * @param value The value to add to the map.
   * @return True if value was stored successfully, or false if not.
   */
   bool insert(string key, string value);

  /**
   * Updates a value into this map according to it's search key.
   * @pre The key to the new value differs from all other search keys in 
   *   this map.
   * @post If store is successful, the value is in proper position in 
   *   this map.
   * @param key The search key associated with value to be stored.
   * @param value The value to add to the map.
   * @return True if value was stored successfully, or false if not.
   */
   bool update(string key, string value);


  /**
   * Removes a value from this map according to it's search key.
   * @post If the value whose search key equals key existed in this map, 
   *   value was removed.
   * @param key The search key associated with the value to be removed.
   * @return True if value was removed successfully, or false if not.
   */
   bool remove(string key);

  /**
   * Removes all entries in this map.
   */
   void drop();

  /**
   * Checks whether this map is empty.
   * @return True if the map is empty, false if not.
   */
   bool isEmpty();

  /**
   * Gets number of items in this map.
   * @return Number of key-value pairs (elements) in this map.
   */
   int getSize();

   /**
   * Default Constructor
   */
   StringMap();
   
  /**
   * Deconstructor
   */
   ~StringMap();
};

#endif


  
