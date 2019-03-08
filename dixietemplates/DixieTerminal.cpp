/*
******************************************************************************************
Title:       DixieTerminal.cpp
Author:      Megan Williams
Created on:  10/09/2014
Description: Implementtion file for DixieTerminal class for the dixielib library. 
*******************************************************************************************
*/
#include "DixieTerminal.h"




//---------------------------------------------------------------
// FUNCTION: readFile
// PURPOSE:  opens and reads a file into an array buffer
// INPUT:    string - filename
// RETURN:   pointer to character buffer
//---------------------------------------------------------------
char *DixieTerminal::readFile(string filename)
{
    ifstream file(filename.c_str(), ios::binary);  // create an input stream
    file.seekg(0, ios::end);                       // position to end of file...
    streamsize size = file.tellg();                // ...so that we can tell how big it is
    file.seekg(0, ios::beg);                       // reset out position back to begining of file
    char *buffer = new char[size+1];               // create space for file and a zero terminator 
    file.read(buffer, size);                       // read into buffer
    buffer[size+1] = 0;                            // make buffer into potential c-string
    return (buffer);                               // return buffer pointer 
}

//---------------------------------------------------------------
// FUNCTION: isPrime
// PURPOSE:  takes a number and checks whether it is prime 
// INPUT:    int number
// RETURN:   1 if number is prime
//---------------------------------------------------------------

bool DixieTerminal::isPrime(int number)
{
    bool r = true;
    
    for (int i = 2; i < number; i++) 
    {
	if (number % i == 0 && i != number) 
        {
            r = false;
	    break;
	}
    }
    
    return(r);
}

//----------------------------------------------------------------
// FUNCTION: dixieString
// PURPOSE: convert a int to a string 
// INPUT:  int
// RETURN: converted string
//----------------------------------------------------------------
string DixieTerminal::dixieString(int d)
{
    string rstr ="";    //return string
    ostringstream o;    //creates a output stream on a string
    if (!(o << d))      //takes integer and writes it to the stream
	rstr ="0.0";    //if it fails it reassigns it to 0.0
    else
        rstr = o.str(); //takes stream and converts to a string

    return (rstr);      //returns converted string
}

//----------------------------------------------------------------
// FUNCTION: dixieString
// PURPOSE: convert a double to a string 
// INPUT:  double 
// RETURN: converted string
//----------------------------------------------------------------
string DixieTerminal::dixieString(double d)
{
    string rstr ="";    //return string
    ostringstream o;    //creates a output stream on a string
    if (!(o << d))      //takes double and writes it to the stream
	rstr ="0.0";    //if it fails it reassigns it to 0.0
    else
        rstr = o.str(); //takes stream and converts to a string

    return (rstr);      //returns converted string
}

//----------------------------------------------------------------
// FUNCTION: dixieString
// PURPOSE: convert a float to a string 
// INPUT:  float 
// RETURN: converted string
//----------------------------------------------------------------
string DixieTerminal::dixieString(float d)
{
    string rstr ="";    //return string
    ostringstream o;    //creates a output stream on a string
    if (!(o << d))      //takes float and writes it to the stream
	rstr ="0.0";    //if it fails it reassigns it to 0.0
    else
        rstr = o.str(); //takes stream and converts to a string

    return (rstr);      //returns converted string
}
//----------------------------------------------------------------
// FUNCTION: print2
// PURPOSE: prints a string with no linefeed
// INPUT:  string 
// RETURN: n/a
//----------------------------------------------------------------
void DixieTerminal::print2(string s)
{
    cout << s;
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
// FUNCTION: print
// PURPOSE: prints a string with linefeed
// INPUT:  string 
// RETURN: n/a
//----------------------------------------------------------------
void DixieTerminal::print(string s)
{
    cout << s << endl;
}

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
// FUNCTION: newLine
// PURPOSE: prints a newline
// INPUT:  n/a
// RETURN: n/a
//----------------------------------------------------------------
void DixieTerminal::newLine()
{
    cout << endl;
}

//----------------------------------------------------------
// FUNCTION: userEnteredString
// PURPOSE: returns a user entered string 
// INPUT:  string
// RETURN: string
//----------------------------------------------------------
string DixieTerminal::userEnteredString(string prompt)
{
    setTtyColor(properties.tty_menu);

    string d;
    do{ 
	cout << prompt << ":";
        if(!(cin >> d))
            cin.clear(); // handle fail...
        cin.ignore();    // ignore the return char
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

void DixieTerminal::printMainArgs(int c, char ** v)
{
    for(int i=0; i<c; i++)
    {
        print( "argc:" + dixieString(i) + "=" + string(v[i]) );
    }
    return;
}

//------------------------------------------------------
// FUNCTION: randomInt
// PURPOSE: returns a random int between low- high 
//          range is from low to high 
// INPUT:  int low, int high
// RETURN: int
//-----------------------------------------------------
int  DixieTerminal::randomInt(int low, int high)
{
  //-------------------------------------------------
  // There's like a billion ways to do this...
  // Got this from stackoverflow.com - it works :-)
  //-------------------------------------------------
    int r = rand() %( high - low + 1 ) + low;
    return(r);
}

//------------------------------------------------------
// FUNCTION: randomFloat
// PURPOSE: returns a random floating point number
//          range is from low to high 
// INPUT:  float low, float high
// RETURN: float 
//-----------------------------------------------------
float DixieTerminal::randomFloat(float low, float high)
{
  //-------------------------------------------------
  // There's like a billion ways to do this...
  // but compiler didn't like doing modulo operation
  // on a float ( -- I guess that IS retarded lol)
  // so, just decided to convert it to int times 100
  // then calulate random range as int 
  // then make it a float divided by 100...
  //------------------------------------------------
    int l = (int) low*100;
    int h = (int) high*100;

    float r = (float) (rand()%( h - l + 1 ) + l);
    r = r/100.00;

    return(r);
}

//-----------------------------------------------
// FUNCTION: setRandomSeed
// PURPOSE: set random number seed 
// INPUT: seed_value
// RETURN: void 
//-----------------------------------------------
void DixieTerminal::setRandomSeed(int seed_value)
{
    if(seed_value > 0)
    {
        //------------------------
        // use the seed_value if 
        // its greater than 0
        //------------------------
        srand(seed_value);
    }
    else
    {
        //--------------------------------------------
        // otherwise we use the current time
        // which is some big int like milliseconds 
        // since 1980 (or something) :-)
        //--------------------------------------------
        srand(time(0));
    }
    return;
}


//--------------------------------------
// FUNCTION: setDecimalPrecision
// PURPOSE: sets cout decimal precsion
//
// INPUT:  int precsion
// RETURN: void
//--------------------------------------
void DixieTerminal::setDecimalPrecision(int p)
{
    cout.precision(p);
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
    cerr << err << endl;
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
    cerr << err << endl;
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
    cerr << m << endl;
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
    {
        cout << "\33[3"<<c<<"m"; // set output color
    } 
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

//-----------------------------------------------------------
// FUNCTION: DixieTerminal()
// PURPOSE:  set default properties 
//-----------------------------------------------------------
void DixieTerminal::setAllowColor(bool flag)
{
    properties.allowTerminalColor=flag;
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

    properties.tty_menu_banner  = TTY_MENU_BANNER;
    properties.tty_menu         = TTY_MENU;
    properties.tty_data         = TTY_DATA;
    properties.tty_normal       = TTY_NORMAL;
    properties.current_color    = TTY_NORMAL;
    properties.allowTerminalColor=true; //yes to color
}

//-----------------------------------------------------------
// FUNCTION: DixieTerminal()
// PURPOSE: Default constructor
//-----------------------------------------------------------
DixieTerminal::DixieTerminal()
{
    defaultProperties();
}

