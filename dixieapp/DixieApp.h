//-----------------------------------------------------------------
// DixieApp.h       Definition file for DixieApp.cpp
//-----------------------------------------------------------------

#ifndef DIXIEAPP_H
#define DIXIEAPP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
class DixieApp;

#include <Properties.h>
#include <HashMap.h>

using namespace std;
//
//--------------------------------------------------
// DixieApp is the base class for any libdixie  
// based applications.
//--------------------------------------------------
class Properties;
class DixieApp
{
    private:
    public:
    
    virtual void start(int, char **) =0;

    Properties *config;
    
    bool   isFile(string);
    long   fileSize(string);
    char  *readFile(string);
    bool   writeFile(string, char *, long);
    bool   writeFile(string, char *);
    string randomString(int);
    string dixieString(char);
    string dixieString(int);
    string dixieString(long);    
    string dixieString(float);
    string dixieString(double);
    void   print(char *, long);
    void   print(string);
    void   print2(string);
    void   newLine(void);
    float  randomFloat(float, float );
    int    randomInt(int, int);
    bool   isPrime(int);
    void   setRandomSeed(int);
    void   setDecimalPrecision(int);
    string getVersion();
    string getSerialNumber();
    
    DixieApp();
};

#endif
