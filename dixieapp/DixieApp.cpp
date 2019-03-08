/*
******************************************************************************************
Title:       DixieApp.cpp
Author:      Megan Williams

Description: Implementation file for DixieApp class for the dixielib library. 
*******************************************************************************************
*/
#include "DixieApp.h"
#include "build.h"


//---------------------------------------------------------------
// FUNCTION: isFile
// PURPOSE:  checks the existance of a file by filename
// INPUT:    string - filename
// RETURN:   bool   - true or false
//---------------------------------------------------------------
bool DixieApp::isFile(string filename)
{
    bool r;
    ifstream file(filename.c_str(), ios::binary);

    if(file)
	r=true;
    else
	r=false;
    
    file.close();
    return(r);
}


//---------------------------------------------------------------
// FUNCTION: fileSize
// PURPOSE:  opens and gets size of a file
// INPUT:    string - filename
// RETURN:   size as long integer
//---------------------------------------------------------------
long DixieApp::fileSize(string filename)
{
    ifstream file(filename.c_str(), ios::binary);  // create an input stream
    if(!file)
	return(0);                                 // return null pointer if file doesn't exist
    file.seekg(0, ios::end);                       // position to end of file...
    streamsize size = file.tellg();                // ...so that we can tell how big it is
    file.close();                                  // close stream.
    return ((long)size);                           // return size of file  
}

//---------------------------------------------------------------
// FUNCTION: readFile
// PURPOSE:  opens and reads a file into an array buffer
// INPUT:    string - filename
// RETURN:   pointer to character buffer
//---------------------------------------------------------------
char *DixieApp::readFile(string filename)
{
    ifstream file(filename.c_str(), ios::binary);  // create an input stream
    if(!file)
	return(0);                                 // return null pointer if file doesn't exist
    file.seekg(0, ios::end);                       // position to end of file...
    streamsize size = file.tellg();                // ...so that we can tell how big it is
    file.seekg(0, ios::beg);                       // reset out position back to begining of file
    char *buffer = new char[size+1];               // create space for file and a zero terminator 
    file.read(buffer, size);                       // read into buffer
    buffer[size] = 0;                              // make buffer into potential c-string
    file.close();                                  // close stream.
    return (buffer);                               // return buffer pointer 
}

//---------------------------------------------------------------
// FUNCTION: writeFile
// PURPOSE:  opens and writes a file from an array buffer
// INPUT:    string - filename
//           char * - array buffer
//           int    - size of array buffer
//
// RETURN:   bool   - true if successful
//---------------------------------------------------------------
bool DixieApp::writeFile(string filename, char *buffer, long size)
{
    // create an output stream
    ofstream file(filename.c_str(), ios_base::binary  | ios_base::trunc);
    file.write(buffer, size);  // write from buffer
    file.close();              // close file
    return(true);              // return OK 
}

//---------------------------------------------------------------
// FUNCTION: writeFile
// PURPOSE:  opens and writes a file from a 0 terminated
//           array buffer
//
// INPUT:    string - filename
//           char * - array buffer
//
// RETURN:   bool   - true if successful
//---------------------------------------------------------------
bool DixieApp::writeFile(string filename, char *buffer)
{
    //-------------------------------------------------
    // This version assumes a text buffer with
    // zero termination... so we have to count bytes
    //-------------------------------------------------
    long size = 0;
    for(int i=0; buffer[i]; i++)
        size++;
    return(writeFile(filename, buffer, size));
}


//---------------------------------------------------------------
// FUNCTION: isPrime
// PURPOSE:  takes a number and checks whether it is prime 
// INPUT:    int number
// RETURN:   1 if number is prime
//---------------------------------------------------------------
bool DixieApp::isPrime(int number)
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
// FUNCTION: randomString
//
// PURPOSE: generate a random alpha-numeric string of length len
//
// INPUT:   int    -- length of string
// RETURN:  string -- returned string 
//
// Notes:  found this on stackoverflow...
//----------------------------------------------------------------
string DixieApp::randomString(int len)
{
    char s[21];
    if(len > 20 || len < 1)
	return ("");
    static const char alphanum[] = "0123456789"
	                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";
    for(int i=0; i < len; ++i)
    {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;

    return (string(s));
}


    
//----------------------------------------------------------------
// FUNCTION: dixieString
// PURPOSE: convert a char to a string 
// INPUT:  char
// RETURN: converted string
//----------------------------------------------------------------
string DixieApp::dixieString(char d)
{
    string rstr ="";
    ostringstream o;
    if (!(o << d))
	rstr ="0";
    else
        rstr = o.str();

    return (rstr); 
}

//----------------------------------------------------------------
// FUNCTION: dixieString
// PURPOSE: convert a int to a string 
// INPUT:  int
// RETURN: converted string
//----------------------------------------------------------------
string DixieApp::dixieString(int d)
{
    string rstr ="";
    ostringstream o;
    if (!(o << d))
	rstr ="0";
    else
        rstr = o.str();

    return (rstr); 
}

//----------------------------------------------------------------
// FUNCTION: dixieString
// PURPOSE: convert a long to a string 
// INPUT:  long
// RETURN: converted string
//----------------------------------------------------------------
string DixieApp::dixieString(long d)
{
    string rstr ="";
    ostringstream o;
    if (!(o << d))
	rstr ="0";
    else
        rstr = o.str();

    return (rstr); 
}

//----------------------------------------------------------------
// FUNCTION: dixieString
// PURPOSE: convert a double to a string 
// INPUT:  double 
// RETURN: converted string
//----------------------------------------------------------------
string DixieApp::dixieString(double d)
{
    string rstr ="";
    ostringstream o;
    if (!(o << d))
	rstr ="0.0";
    else
        rstr = o.str();

    return (rstr); 
}

//----------------------------------------------------------------
// FUNCTION: dixieString
// PURPOSE: convert a float to a string 
// INPUT:  float 
// RETURN: converted string
//----------------------------------------------------------------
string DixieApp::dixieString(float d)
{
    string rstr ="";
    ostringstream o;
    if (!(o << d))
	rstr ="0.0";
    else
        rstr = o.str();

    return (rstr); 
}
//----------------------------------------------------------------
// FUNCTION: print2
// PURPOSE: prints a string with no linefeed
// INPUT:  string 
// RETURN: n/a
//----------------------------------------------------------------
void DixieApp::print2(string s)
{
    cout << s;
}


//----------------------------------------------------------------
// FUNCTION: print
// PURPOSE: prints a string with linefeed
// INPUT:  string 
// RETURN: n/a
//----------------------------------------------------------------
void DixieApp::print(string s)
{
    cout << s << endl;
}


//----------------------------------------------------------------
// FUNCTION: print
// PURPOSE: prints a c_string 
// INPUT:  char * -- char buffer
//         long   -- long size
// RETURN: n/a
//----------------------------------------------------------------
void DixieApp::print(char *buffer, long size)
{
    cout.write(buffer,size);

}
//----------------------------------------------------------------
// FUNCTION: newLine
// PURPOSE: prints a newline
// INPUT:  n/a
// RETURN: n/a
//----------------------------------------------------------------
void DixieApp::newLine()
{
    cout << endl;
}


//------------------------------------------------------
// FUNCTION: randomInt
// PURPOSE: returns a random int between low- high 
//          range is from low to high 
// INPUT:  int low, int high
// RETURN: int
//-----------------------------------------------------
int  DixieApp::randomInt(int low, int high)
{
  //-------------------------------------------------
  // There's like a billion ways to do this...
  // Got this from stackoverflow.com 
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
float DixieApp::randomFloat(float low, float high)
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
void DixieApp::setRandomSeed(int seed_value)
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
void DixieApp::setDecimalPrecision(int p)
{
    cout.precision(p);
}


//----------------------------------------
// Get serial number and version
//-----------------------------------------
string DixieApp::getSerialNumber()
{
    return SERIAL;
}

string DixieApp::getVersion()
{
    return VERSION;
}

//-----------------------------------------------------------
// FUNCTION: DixieApp()
// PURPOSE: Default constructor
//-----------------------------------------------------------
DixieApp::DixieApp()
{
    srand (time(NULL));
    
    //----------------------------------------------
    // Set cout properties...
    //----------------------------------------------
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);

    //-----------------------------------------------
    // We need this...
    //-----------------------------------------------
    config = new Properties();
}
