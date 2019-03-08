#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <DixieApp.h>

#include <NameValue.h>
#include <HashMap.h>

using namespace std;

class Properties 
{
    private:
    HashMap<NameValue> hash;
    //------------------------------------------------
    // This is a pointer to application context
    //------------------------------------------------
    DixieApp *applicationContext;
    //---------------------------------------------------
    // This flag protects against invalid pre-conditions
    //---------------------------------------------------
    bool isOpen;
    //------------------------------------------------
    // This is the filename for the data file
    //------------------------------------------------
    string propertiesFile;
    //------------------------------------------------
    // This is the error message string
    //------------------------------------------------
    string errorMessage;
    
    public:
    string get(string);
    int    getInt(string);
    char   getChar(string);
    short  getShort(string);
    long   getLong(string);
    float  getFloat(string);
    double getDouble(string);
    bool   getBool(string);

    void   put(string, string);

    bool   open(string, DixieApp *);
    bool   save();
    bool   load();
    bool   parseInsert(char *);    

    Queue<NameValue> *dump();    
};



#endif
