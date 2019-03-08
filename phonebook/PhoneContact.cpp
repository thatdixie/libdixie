#include "PhoneContact.h"

//-----------------------------------
// just in case we want to create
// a dummy/test record
//-----------------------------------
void PhoneContact::initDbRecord()
{
    name    ="test";
    nickname="test";
    phone   ="555-5555";
    email   ="test@ThatDixie.com";
    key1    ="test1";
    key2    ="test2";
    key3    ="test3";
    key4    ="test4";    
}

//-------------------------------
// default constructor
//-------------------------------
PhoneContact::PhoneContact()
{
    //----------------------------------
    // we just make sure these things
    // are always initialized to empty
    //----------------------------------
    name    ="";
    nickname="";
    phone   ="";
    email   ="";
    key1    ="";
    key2    ="";
    key3    ="";
    key4    ="";
}

