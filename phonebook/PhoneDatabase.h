#ifndef PHONEDATABASE_H
#define PHONEDATABASE_H

#include <DixieMenu.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include "PhoneContact.h"
#include "PhoneHashTable.h"

using namespace std;

class PhoneDatabase
{
     private:
    //-------------------------------------------------
    // This is the HashMap of PhoneContact records.
    //-------------------------------------------------
    PhoneHashTable        *phoneHashTable;
    //------------------------------------------------
    // This is a pointer to application context
    //------------------------------------------------
    DixieApp              *applicationContext;
    //---------------------------------------------------
    // This flag protects against invalid pre-conditions
    //---------------------------------------------------
    bool                   isOpen;
    //------------------------------------------------
    // This is the filename for the data file
    //------------------------------------------------
    string                 phoneData;
    //------------------------------------------------
    // This is the error message string
    //------------------------------------------------
    string                 errorMessage;
    
    public:
    bool         open(string, DixieApp *);    
    PhoneContact searchPhoneBook(string);
    bool         addContact(PhoneContact);
    bool         updateContact(PhoneContact);
    bool         removeContact(PhoneContact);
    bool         load();    
    bool         parseInsert( char *);
    bool         save();
    string       toLowerCase(string);
    string       getErrorMessage();
    
                 PhoneDatabase();    
                ~PhoneDatabase();    
};

#endif


  
