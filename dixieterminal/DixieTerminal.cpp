/*
******************************************************************************************
Title:       DixieTerminal.cpp
Author:      Megan Williams

Description: Implementation file for DixieTerminal class for the dixielib library. 
*******************************************************************************************
*/
#include "DixieTerminal.h"


//----------------------------------------------------------------
// FUNCTION: print
// PURPOSE: sets color and prints a string
// INPUT:  string 
// RETURN: n/a
//----------------------------------------------------------------
void DixieTerminal::print(string s, char color)
{
    char save = properties.current_color;

    setTtyColor(color);    
    cout << s << endl;
    setTtyColor(save);        
}

//----------------------------------------------------------------
// FUNCTION: print
// PURPOSE: sets color and prints a string
// INPUT:  string 
// RETURN: n/a
//----------------------------------------------------------------
void DixieTerminal::print(string s)
{
    cout << s << endl;    
}

//----------------------------------------------------------------
// FUNCTION: print2
// PURPOSE: sets color and prints a string
// INPUT:  string 
// RETURN: n/a
//----------------------------------------------------------------
void DixieTerminal::print2(string s, char color)
{
    char save = properties.current_color;

    setTtyColor(color);    
    cout << s;
    setTtyColor(save);        
}

//----------------------------------------------------------------
// FUNCTION: print2
// PURPOSE: prints a string
// INPUT:  string 
// RETURN: n/a
//----------------------------------------------------------------
void DixieTerminal::print2(string s)
{
    cout << s;    
}


//----------------------------------------------------------
// FUNCTION: userEnteredString
// PURPOSE: returns a user entered string 
// INPUT:  string -- user prompt
// RETURN: string -- user enered string
//----------------------------------------------------------
string DixieTerminal::userEnteredString(string prompt)
{
    setTtyColor(properties.tty_menu);

    string d;
    do{ 
	cout << prompt << ":";
        getline(cin, d);
    }while(d =="");

    return(d);
}

//----------------------------------------------------------
// FUNCTION: userEnteredDouble
// PURPOSE: returns a user entered doublenumber 
// INPUT:  double low, double high
// RETURN: double
//----------------------------------------------------------
double DixieTerminal::userEnteredDouble(string prompt, double low, double high)
{
    setDecimalPrecision(1);
    setTtyColor(properties.tty_menu);

    double d;
    do{ 
	cout << prompt << " between ("<<low<<"-"<<high<<"):";
        if(!(cin >> d))
            cin.clear(); // handle fail...
        cin.ignore();    // ignore the return char
    }while((d < low) || (d > high));

    return(d);
}

//----------------------------------------------------------
// FUNCTION: userEnteredFloat
// PURPOSE: returns a user entered floating point number 
// INPUT:  float low, float high
// RETURN: float 
//----------------------------------------------------------
float DixieTerminal::userEnteredFloat(string prompt, float low, float high)
{
    setDecimalPrecision(1);
    setTtyColor(properties.tty_menu);

    float d;
    do{ 
	cout << prompt << " between ("<<low<<"-"<<high<<"):";
        if(!(cin >> d))
            cin.clear(); // handle fail...
        cin.ignore();    // ignore the return char
    }while((d < low) || (d > high));

    return(d);
}

//--------------------------------------------------------
// FUNCTION: userEnteredInt
// PURPOSE: returns a user entered  int between low- high 
// INPUT:  int low, int high
// RETURN: int
//--------------------------------------------------------
int  DixieTerminal::userEnteredInt(string prompt, int low, int high)
{
    int d;
    setTtyColor(properties.tty_menu);

    do{ 
        cout << prompt <<" between ("<<low<<"-"<<high<<"):";
        if(!(cin >> d))
            cin.clear(); // handle fail...
        cin.ignore();    // ignore the return char
    }while((d < low) || (d > high));

    return(d);
}

/**
 * print prompt and returns if Y or y pressed
 * 
 * @param  string -- prompt to display
 * @return bool   -- true on 'Y', false on 'N'
 */
bool DixieTerminal::yesPlease(string prompt)
{
    char yOrN;
    bool r;
    bool notDone = true;    
    do
    {
        print2(prompt+": (Y/N)");
	yOrN = getOneChar();
	if(yOrN == 'N' || yOrN =='n')
        {
	    notDone = false;
            r = false;	    	    
        }
	else if(yOrN == 'Y' || yOrN =='y')
	{
	    notDone = false;
            r = true;	    
	}
	newLine();
    }while(notDone);
    
    return(r);
}

/**
 * print prompt and returns true if N or N pressed
 * 
 * @param  string -- prompt to display
 * @return bool   -- true on 'Y', false on 'N'
 */
bool DixieTerminal::noThankYou(string prompt)
{
    //--------------------------------
    // return oppisite of yesPlease()
    //--------------------------------
    if(yesPlease(prompt))
	return(false);
    else
	return(true);
}

//----------------------------------------------
// FUNCTION:pressAnyKey
// PURPOSE: prints "press any key to continue"
//          and uses getOneChar()
//
// INPUT:  void
// RETURN: void
//----------------------------------------------
void DixieTerminal::pressAnyKey()
{
    setTtyColor(properties.tty_menu);
    cout << "press any key to continue...";
    getOneChar();
}

//---------------------------------------------------------
// FUNCTION:getOneChar
// PURPOSE: gets JUST ONE char
//          uses linux "stty raw" command 
//          to set "raw mode" and "stty cooked" to 
//          reseet back to normal 
// SEE ALSO:
//           type 'man system'  
//           and  'man stty' on terminal command line
// 
// INPUT:  void
// RETURN: char
//--------------------------------------------------------
char DixieTerminal::getOneChar()
{
    system ("stty raw");
    char c = cin.get();
    system ("stty cooked");
    return(c);
}

//-----------------------------------------------------------
// FUNCTION:errorExit()
// PURPOSE: 1) prints a message to standard error stream
//          2) and exits program with an error code
//          3) it also sets tty color back to normal 
// 
// INPUT:  string=error string 
//         int = error code
// RETURN: void
//-----------------------------------------------------------
void DixieTerminal::errorExit(string err, int code)
{
    setTtyColor(properties.tty_data);
    cout << err << endl;
    setTtyColor(properties.tty_normal);
    exit(code);
}

//-----------------------------------------------------------
// FUNCTION:errorContinue()
// PURPOSE: 1) prints a message to standard error stream
//          2) uses pressAnyKey() so user may continue
// 
// INPUT:  string=error string 
// RETURN: void
//-----------------------------------------------------------
void DixieTerminal::errorContinue(string err)
{
    setTtyColor(properties.tty_data);
    cout << err << endl;
    pressAnyKey();
}

//-----------------------------------------------------------
// FUNCTION:exitOK()
// PURPOSE: 1) prints a message to standard error stream
//          2) and exits program with code EXIT_OK
//          3) it also sets tty color back to normal 
// 
// INPUT:  string=exit string 
// RETURN: void
//-----------------------------------------------------------
void DixieTerminal::exitOK(string m)
{
    setTtyColor(properties.tty_data);
    cout << m << endl;
    setTtyColor(properties.tty_normal);
    exit(EXIT_OK);
}

//-----------------------------------------------------------
// FUNCTION:setTtyColor()
// PURPOSE: This sets the foreground color of the terminal using 
//          the ANSI standard "Escape Sequence"  
// SEE ALSO:
//          http://en.wikipedia.org/wiki/ANSI_escape_code         
// 
// INPUT:  char=color code
// RETURN: void
//-----------------------------------------------------------
void DixieTerminal::setTtyColor(char c)
{
    if(properties.allowTerminalColor)
    cout << "\33[3"<<c<<"m"; // set output color 
    properties.current_color =c;
}
//-----------------------------------------------------------
// FUNCTION:getTtyColor()
// PURPOSE: gets the current tty color
// 
// INPUT:  void
// RETURN: char - ANSI color code
//-----------------------------------------------------------
char DixieTerminal::getTtyColor()
{
    return(properties.current_color);
}

//----------------------------------------
// Setters methods for TTY colors
//-----------------------------------------
void DixieTerminal::setAllowColor(bool flag)
{
    properties.allowTerminalColor=flag;
}
void DixieTerminal::setTtyNormal(char c)
{
    properties.tty_normal = c;
}

//-----------------------------------------------------------
// FUNCTION: DixieTerminal()
// PURPOSE:  set default properties 
//-----------------------------------------------------------
void DixieTerminal::defaultProperties()
{
    //----------------------------------------------
    // Set cout properties...
    //----------------------------------------------
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    
    config->put("tty_normal"        ,dixieString(TTY_NORMAL));
    config->put("tty_data"          ,dixieString(TTY_NORMAL));
    config->put("current_color"     ,dixieString(TTY_NORMAL));
    config->put("allowTerminalColor","true"); //yes to color
    
    properties.tty_normal       = config->getChar("tty_normal");
    properties.tty_data         = config->getChar("tty_data");
    properties.current_color    = config->getChar("current_color");
    properties.allowTerminalColor=config->getBool("allowTerminalColor");
}


//-----------------------------------------------------------
// FUNCTION: DixieTerminal()
// PURPOSE: Default constructor
//-----------------------------------------------------------
DixieTerminal::DixieTerminal()
{
    defaultProperties();
}
