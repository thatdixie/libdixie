//-----------------------------------------------------------------
// DixieTerminal.h       Definition file for DixieTerminal.cpp
//-----------------------------------------------------------------
#ifndef DIXIETERMINAL_H
#define DIXIETERMINAL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

//------------------------------------
// DixieTerminal constants
//------------------------------------
//    tty foreground colors
//-----------------------------------
const char  TTY_BLACK        ='0';
const char  TTY_RED          ='1';
const char  TTY_GREEN        ='2';
const char  TTY_YELLOW       ='3';
const char  TTY_BLUE         ='4';
const char  TTY_MAGENTA      ='5';
const char  TTY_CYAN         ='6';
const char  TTY_NORMAL       =TTY_BLACK;
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
struct Properties
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
// menu driven applications.
//--------------------------------------------------
class DixieTerminal
{
    private:

    Properties properties;
    void defaultProperties(void);

    public:


    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function: Takes a filename opens and reads into an array buffer and returns pointer to char array.
     *****************************************************************************************************
     */
    char *readFile(string);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Takes an integer and returns true if it is a Prime number.
     *****************************************************************************************************
     */
    bool isPrime(int);
    
     /****************************************************************************************************
     * Preconditon:  An instance of DixieTerminal has been created.
     * Function:     Polymorphic dixieString converts an integer into a string safely.
     *****************************************************************************************************
     */
    string dixieString(int);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Polymorphic dixiString converts a float to a string safely.
     *****************************************************************************************************
     */ 
    string dixieString(float);


    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Polymorphic dixiString converts a double to a string safely.
     *****************************************************************************************************
     */
    string dixieString(double);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Polymorphic print outputs a string with linefeed.
     *****************************************************************************************************
     */
    void   print(string);

    /*****************************************************************************************************
     * Precondition: An instance of Dixiemenu has been created.
     * Function:     Polymorphic print outputs a string with linefeed and char color choice.
     *****************************************************************************************************
     */
    void   print(string, char);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Polymorphic print2 outputs a string without linefeed.
     *****************************************************************************************************
     */
    void   print2(string);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Polymorphic print2 outputs a string without linefeed and char color choice.
     *****************************************************************************************************
     */
    void   print2(string, char);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Polymorphic newLine outputs a new line.
     *****************************************************************************************************
     */
    void   newLine(void);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     userEnterdString prompts user and returns user input as a string.
     *****************************************************************************************************
     */
    string userEnteredString(string);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     userEnteredDouble prompts user with a range and returns user input as a double.
     *****************************************************************************************************
     */
    double userEnteredDouble(string, double, double );

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     userEnteredFloat prompts user with a range and returns user input as a float.
     *****************************************************************************************************
     */
    float  userEnteredFloat(string, float, float );

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     userEnteredFloat prompts user with a range and returns user input as an integer.
     *****************************************************************************************************
     */
    int    userEnteredInt(string, int, int);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     randomFloat outputs a random float between range input using rand().
     *****************************************************************************************************
     */
    float  randomFloat(float, float );

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     randomInt outputs a random integer between range input using rand().
     *****************************************************************************************************
     */
    int    randomInt(int, int);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     pressAnyKey prompts user and returns char using getOneChar().
     *****************************************************************************************************
     */
    void   pressAnyKey(void);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     errorExit prints a message to standard error stream and exits program 
     *               with an error code it also sets tty color back to normal 
     *****************************************************************************************************
     */
    void   errorExit(string, int);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     prints a message to standard error stream uses pressAnyKey() so user may continue             
     *****************************************************************************************************
     */
    void   errorContinue(string);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     prints a message to standard error stream and exits program with code EXIT_OK 
     *               it also sets tty color back to normal             
     *****************************************************************************************************
     */
    void   exitOK(string);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     gets JUST ONE char uses linux "stty raw" command to set "raw mode" and 
     *               "stty cooked" to reseet back to normal             
     *****************************************************************************************************
     */
    char   getOneChar(void);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     gets the current tty color and returns char - ANSI color code             
     *****************************************************************************************************
     */
    char   getTtyColor(void);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     This sets the foreground color of the terminal using the ANSI standard 
     *               "Escape Sequence"             
     *****************************************************************************************************
     */
    void   setTtyColor(char);

    /***************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets random number seed using seed_value if its greater than 0, otherwise uses 
     *               current time in milliseconds             
     *****************************************************************************************************
     */
    void   setRandomSeed(int);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets cout decimal precision             
     *****************************************************************************************************
     */
    void   setDecimalPrecision(int);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets menu title with string input             
     *****************************************************************************************************
     */
    void   setMenuTitle(string);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets menu prompt with string input            
     *****************************************************************************************************
     */
    void   setMenuPrompt(string);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets invalid selection with string input            
     *****************************************************************************************************
     */
    void   setInvalidSelection(string);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets banner with char input              
     *****************************************************************************************************
     */
    void   setBannerChar(char);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets banner color with char input              
     *****************************************************************************************************
     */
    void   setTtyBanner(char);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets menu color with char input              
     *****************************************************************************************************
     */
    void   setTtyMenu(char);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets data color with char input              
     *****************************************************************************************************
     */
    void   setTtyData(char);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets color with char input              
     *****************************************************************************************************
     */
    void   setTtyNormal(char);

    /*****************************************************************************************************
     * Precondition: An instance of DixieTerminal has been created.
     * Function:     Sets Allow Color configuration              
     *****************************************************************************************************
     */
    void   setAllowColor(bool);

    /*****************************************************************************************************
     * Precondition: N/A
     * Function:     Default Constructor              
     *****************************************************************************************************
     */


    void printMainArgs(int,char **);


    DixieTerminal();

};

#endif
