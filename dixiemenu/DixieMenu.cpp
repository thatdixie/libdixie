/*
******************************************************************************************
Title:       DixieMenu.cpp
Author:      Megan Williams
Created on:  10/09/2014

Description: Implementation file for DixieMenu class for the dixielib library. 
*******************************************************************************************
*/
#include "DixieMenu.h"

//---------------------------------------------------------------
// FUNCTION: mainMenu
//
// PURPOSE:  this is the main entry for the menu it will
//           print the banner and menu items, set colors and 
//           execute selected functions -- this function never
//           returns and expects that one of the functions 
//           uses exitOK() to terminate the program.  
//
// INPUT:    none
// RETURN:   N/A
//---------------------------------------------------------------
void DixieMenu::mainMenu()
{
    makeBanner(); 

    for(;;)    //forever...
    {
        setTtyColor(properties.tty_menu_banner);// set color for menu banner
        printMenuBanner();                      // display banner
        setTtyColor(properties.tty_menu);       // set color for menu items
        for(int i=0; i < menuItemCount; i++)    // display menu items and prompt
        {
	  printMenuItem(i);                     
        }
        printPrompt();                          // display user prompt
        executeMenuItem(getOneChar());          // get user selection and execute function
    }
}

//---------------------------------------------------------------
// FUNCTION: printMenuItem
//
// PURPOSE:  displays a menu item 
//
// INPUT:    int = index into menu list
//
// RETURN:   N/A
//---------------------------------------------------------------
void DixieMenu::printMenuItem(int x)
{
    string str = "";
    str +=menuItems[x].select;
    str +=" ";
    str += menuItems[x].text;
    cout << str << endl;     
}

//---------------------------------------------------------------
// FUNCTION: executeMenuItem
//
// PURPOSE:  Execute function associated with a menu selection
//
// INPUT: char = menu selection 
// RETURN: N/A
//---------------------------------------------------------------
void DixieMenu::executeMenuItem(char select)
{
    select = toupper(select);  // convert to upper case
    cout << endl;              // and a linefeed...
    for(int i=0; i < menuItemCount; i++)
    {
        if(select == menuItems[i].select)
        {
            setTtyColor(properties.tty_data);// set tty data output... 
	    (this->*menuItems[i].func)();    // invoke the method...
            pressAnyKey();                   // standard "press any key" to continue
	    return;        
        }
    }
    //-------------------------------------------------
    // This only happens if no selection is found...
    //-------------------------------------------------
    errorContinue(properties.invalid_selection);
    return;
}

//---------------------------------------------------------------
// FUNCTION: printMenuBanner
//
// PURPOSE:  add new item to menu list
//
// INPUT:    None
// RETURN:   N/A
//---------------------------------------------------------------
void DixieMenu::printMenuBanner()
{
    cout << endl;
    cout << properties.banner_border << endl;
    cout << properties.banner_title  << endl;
    cout << properties.banner_border << endl;
}

//---------------------------------------------------------------
// FUNCTION: printPrompt
//
// PURPOSE:  add new item to menu list
//
// INPUT:    none
//
// RETURN: N/A
//---------------------------------------------------------------
void DixieMenu::printPrompt()
{
    cout << properties.prompt;
}

//---------------------------------------------------------------
// FUNCTION: addMenuItem
//
// PURPOSE:  add new item to menu list
//
// INPUT:    char   =selector
//           string =menu item display text
//           ACTION_FUNC = pointer to function to execute
//
// RETURN: N/A
//---------------------------------------------------------------
void DixieMenu::addMenuItem(char select, string text, ACTION_FUNC func)
{
    if(menuItemCount < MAX_MENU_ITEMS) // make sure menu not too big
    {
        //------------------------------------------------
        // Initialize menu item...
        //------------------------------------------------
        MenuItem *i = &menuItems[menuItemCount++];
        i->select   = toupper(select);// set selector character
        i->text     = text;           // the menu text
        i->func     = func;           // the function invoked 
    }
}

//---------------------------------------------------------------
// FUNCTION: makeBanner
//
// PURPOSE:  make right sized banner
//
// INPUT:    None
// RETURN:   N/A
//---------------------------------------------------------------
void DixieMenu::makeBanner()
{
    char c = properties.banner_char;
    int  l = 0;
    int  longest=0;
    properties.banner_border +=c;
    properties.banner_border +=c;
    properties.banner_title  =properties.menu_title;

    //------------------------------------------
    // find the longest menu item text length
    //------------------------------------------
    for(int i=0; i < menuItemCount; i++)
    {
        l = menuItems[i].text.length();   
        if (l > longest)
	    longest =l;
    }
    if(longest < properties.menu_title.length())
        longest = properties.menu_title.length();
    //----------------------------------------------
    // make a right sized border
    //----------------------------------------------
    for(int j=0; j < longest; j++)
    {
        properties.banner_border+= properties.banner_char;
    }
    //-----------------------------------------------
    // make a centered banner title
    //-----------------------------------------------
    for(int k=0; k < ((longest/2) - (properties.menu_title.length()/2)); k++)
    {
        properties.banner_title = ' ' + properties.banner_title;
    }
}


//----------------------------------------
// Setters methods for menu properties
//-----------------------------------------
void DixieMenu::setMenuTitle(string s)
{
    properties.menu_title = s;
}
void DixieMenu::setMenuPrompt(string s)
{
    properties.prompt = s;
}
void DixieMenu::setInvalidSelection(string s)
{
    properties.invalid_selection = s;
}
void DixieMenu::setBannerChar(char c)
{
    properties.banner_char = c;
}
//----------------------------------------
// Setters methods for TTY colors
//-----------------------------------------
void DixieMenu::setAllowColor(bool flag)
{
    properties.allowTerminalColor=flag;
}
void DixieMenu::setTtyBanner(char c)
{
    properties.tty_menu_banner = c;
}
void DixieMenu::setTtyMenu(char c)
{
    properties.tty_menu = c;
}
void DixieMenu::setTtyData(char c)
{
    properties.tty_data = c;
}

void DixieMenu::setConfigProperties()
{
    properties.menu_title       = config->get("menu_title");
    properties.tty_menu_banner  = config->getChar("tty_menu_banner");
    properties.tty_menu         = config->getChar("tty_menu");
    properties.tty_data         = config->getChar("tty_data");
    properties.tty_normal       = config->getChar("tty_normal");
    properties.banner_char      = config->getChar("banner_char");
    properties.prompt           = config->get("prompt");
    properties.invalid_selection= config->get("invalid_selection");
    properties.current_color    = config->getChar("current_color");
    properties.allowTerminalColor=config->getBool("allowTerminalColor");
}


//-----------------------------------------------------------
// FUNCTION: DixieTerminal()
// PURPOSE:  set default properties 
//-----------------------------------------------------------
void DixieMenu::defaultProperties()
{
    //----------------------------------------------
    // Set cout properties...
    //----------------------------------------------
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    //---------------------------------------------
    // Set default menu properties...
    //--------------------------------------------- 
    config->put("menu_title"     , MENU_TITLE);
    config->put("tty_menu_banner", dixieString(TTY_MENU_BANNER));
    config->put("tty_menu"       , dixieString(TTY_MENU));
    config->put("tty_data"       , dixieString(TTY_DATA));
    config->put("tty_normal"     , dixieString(TTY_NORMAL));
    config->put("banner_char"    , dixieString(BANNER_CHAR));
    config->put("prompt"         , PROMPT);
    config->put("invalid_selection" ,INVALID_SELECTION);
    config->put("current_color"     ,dixieString(TTY_NORMAL));
    config->put("allowTerminalColor","true"); //yes to color


    properties.menu_title       = config->get("menu_title");
    properties.tty_menu_banner  = config->getChar("tty_menu_banner");
    properties.tty_menu         = config->getChar("tty_menu");
    properties.tty_data         = config->getChar("tty_data");
    properties.tty_normal       = config->getChar("tty_normal");
    properties.banner_border    = EMPTY_STRING;
    properties.banner_title     = EMPTY_STRING;
    properties.banner_char      = config->getChar("banner_char");
    properties.prompt           = config->get("prompt");
    properties.invalid_selection= config->get("invalid_selection");
    properties.current_color    = config->getChar("current_color");
    properties.allowTerminalColor=config->getBool("allowTerminalColor");
    menuItemCount =0;
}


//-----------------------------------------------------------
// FUNCTION: DixieMenu()
// PURPOSE: Default constructor
//-----------------------------------------------------------
DixieMenu::DixieMenu()
{
    defaultProperties();
}
