#ifndef PHONECONTACTS_H
#define PHONECONTACTS_H

#include <HashMap.h>

using namespace std;

/**
 * @class PhoneContacts
 * @brief A map (dictionary) that uses a search key to identify 
 *        PHONE_CONTACT records.
 * @details
 * This implementation delegates to class HashMap using <PHONE_CONTACT> for data.
 * See HashMap.h for implementation details
 */ 
class PhoneContacts
{
    public:
    //-------------------------------------------------
    // This is the dictionary record stored in hashMap.
    //-------------------------------------------------
    class PHONE_CONTACT
    {
        public:
        string name;
        string nickname;
        string phone;
        string email;
    };
    
     private:
    //-------------------------------------------------
    // This is the HashMap of PHONE_CONTACT records.
    //-------------------------------------------------
    HashMap<PHONE_CONTACT> *hashMap;
  
    public:

  /**
   * Retrieves a record with a given search key from this map.
   * @post If retrieval is successful, record is returned.
   * @param key The search key associated with the record to be retrieved.
   * @return The record associated with the search key.
   * @throw If retrieval is not successful, throws an exception.
   */
  PHONE_CONTACT select(string key);

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
   bool insert(string key, PHONE_CONTACT record);

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
   bool update(string key, PHONE_CONTACT record);

  /**
   * Removes a record from this map according to it's search key.
   * @post If the record whose search key equals key existed in this map, 
   *   record was removed.
   * @param key The search key associated with the record to be removed.
   * @return True if record was removed successfully, or false if not.
   */
   bool remove(string key);

   bool   dump(Queue<PHONE_CONTACT> *);


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
   * @return Number of key-record pairs (elements) in this map.
   */
   int getSize();

   /**
   * Default Constructor
   */
   PhoneContacts();
   
  /**
   * Deconstructor
   */
   ~PhoneContacts();
};

#endif


  
