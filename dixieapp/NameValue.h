#ifndef NAMEVALUE_H
#define NAMEVALUE_H

#include <stdlib.h>
#include <string>
#include <cstdlib>
using namespace std;

class NameValue
{
    private:
    string name;
    string value;

    public:
    void   setName( string);
    void   setValue(string);
    string getName();
    string getValue();
    int    intValue();
    char   charValue();
    bool   boolValue();
    long   longValue();
    short  shortValue();
    float  floatValue();
    double doubleValue();
    
    NameValue(string, string);
    NameValue();
};

#endif
