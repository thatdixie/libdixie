#ifndef PHONECONTACT_H
#define PHONECONTACT_H

#include <string>
using namespace std;

//----------------------------------------------------------
// This initialization record may be used to seed
// a new database. If you change the PhoneContact class
// make sure this record reflects that change.
//----------------------------------------------------------
string const DB_INIT_RECORD = "test,test,555-5555,test@ThatDixie.com,test1,test2,test3,test4\n";

    //-------------------------------------------------
    // This is the dictionary record stored in hashMap
    // for Phone Book Application.
    //-------------------------------------------------
    class PhoneContact
    {
        public:
        string name;
        string nickname;
        string phone;
        string email;
        string key1;
        string key2;
        string key3;
        string key4;
        void   initDbRecord();
               PhoneContact();
    };

#endif
