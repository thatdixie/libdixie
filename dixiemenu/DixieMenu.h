//---------------------------------------------------------------
// DixieMenu.h       Definition file for DixieMenu.cpp
//---------------------------------------------------------------
#ifndef DIXIEMENU_H
#define DIXIEMENU_H

#include <DixieTerminal.h>


//------------------------------------
// DixieMenu constants
//------------------------------------
const int    MAX_MENU_ITEMS    = 36;
const string INVALID_SELECTION = "Invalid Selection";
const string MENU_TITLE        = "Menu Options";
const string PROMPT            = "Select:";
const char   BANNER_CHAR       = '=';
const string EMPTY_STRING      ="";
//
//---------------------------------------------------
// Our function pointer to "void func()"
//---------------------------------------------------
class DixieMenu;
typedef void (DixieMenu::*ACTION_FUNC)(void);
//
//--------------------------------------------------
// MenuItem holds a menu function, selector char 
// and display text
//--------------------------------------------------
struct MenuItem
{
    char        select;
    string      text;
    ACTION_FUNC func;
};
//
//--------------------------------------------------
// DixieMenu is the base class for console based 
// menu driven applications.
//--------------------------------------------------
class DixieMenu : public DixieTerminal
{
    private:

    MenuItem   menuItems[MAX_MENU_ITEMS];
    int        menuItemCount;

    void makeBanner(void);
    void printMenuBanner(void);
    void printMenuItem(int);
    void printPrompt(void);
    void executeMenuItem(char);
    void defaultProperties(void);

    public:
    
    void mainMenu(void);
    void addMenuItem(char, string, ACTION_FUNC);

    void   setMenuTitle(string);
    void   setMenuPrompt(string);
    void   setInvalidSelection(string);
    void   setBannerChar(char);
    void   setAllowColor(bool);
    void   setTtyBanner(char);
    void   setTtyMenu(char);
    void   setTtyData(char);
    void   setConfigProperties(void);

    DixieMenu();
};

#endif
