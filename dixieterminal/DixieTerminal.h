//-----------------------------------------------------------------------------
// DixieTerminal.h       Definition file for DixieTerminal.cpp
//-----------------------------------------------------------------------------

#ifndef DIXIETERMINAL_H
#define DIXIETERMINAL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>

#include <DixieApp.h>

using namespace std;

//-----------------------------------
//    tty foreground colors
//-----------------------------------
const char  TTY_BLACK        ='0';
const char  TTY_RED          ='1';
const char  TTY_GREEN        ='2';
const char  TTY_YELLOW       ='3';
const char  TTY_BLUE         ='4';
const char  TTY_MAGENTA      ='5';
const char  TTY_CYAN         ='6';
const char  TTY_NORMAL       ='9';
const char  TTY_MENU         =TTY_BLUE;
const char  TTY_MENU_BANNER  =TTY_CYAN;
const char  TTY_DATA         =TTY_RED;
//------------------------------------
//    exit/error codes
//------------------------------------
const int   EXIT_OK          =0;
const int   FATAL_ERROR      =-1;
//
//--------------------------------------------------
// Properties contains all configurable parameters
//--------------------------------------------------
struct RuntimeProperties
{
    bool   allowTerminalColor;
    char   tty_menu_banner;
    char   tty_menu;
    char   tty_data;
    char   tty_normal;
    string invalid_selection;
    string banner_border;
    string banner_title;
    char   banner_char;
    string prompt;
    string menu_title; 
    char   current_color;
};
//
//--------------------------------------------------
// DixieTerminal is the base class for console based 
// terminal driven applications.
//--------------------------------------------------

class DixieTerminal : public DixieApp
{
    protected:
    RuntimeProperties properties;

    public:
    
    void   print(string);
    void   print2(string);
    void   print(string, char);
    void   print2(string, char);
    string userEnteredString(string);
    double userEnteredDouble(string, double, double );
    float  userEnteredFloat(string, float, float );
    int    userEnteredInt(string, int, int);
    bool   yesPlease(string);
    bool   noThankYou(string);
    void   pressAnyKey(void);
    void   errorExit(string, int);
    void   errorContinue(string);
    void   exitOK(string);
    char   getOneChar(void);
    char   getTtyColor(void);
    void   setTtyColor(char);

    void   setAllowColor(bool);
    void   setTtyNormal(char);
    void defaultProperties(void);
    
    DixieTerminal();
};

#endif
