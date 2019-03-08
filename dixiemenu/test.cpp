
/*
*******************************************************************************************
*/
#include "test.h"
#include <cstring>


void Test::start(int argc, char **argv)
{
    config = new Properties();
    config->open("test.conf", this);
    config->load();
    setConfigProperties();
    
    print(config->get("menu_title"));
    print(dixieString(config->getChar("tty_menu_banner")));
    print(dixieString(config->getChar("tty_menu")));
    print(dixieString(config->getChar("tty_data")));
    print(dixieString(config->getChar("tty_normal")));
    print(dixieString(config->getChar("banner_char")));
    print(config->get("prompt"));
    print(config->get("invalid_selection"));
    print(dixieString(config->getChar("current_color")));
    print(config->get("allowTerminalColor"));

    //-------------------------------------------
    // Sets the Menu Title -- simple enough :-)
    //-------------------------------------------
    setMenuTitle(getVersion());

    //********************************************************************
    // Here we create our Menu:
    //
    // Function in this class <---------------------------
    // Cast to function pointer <-----------             |
    // Description <---                    |             |
    // Selector<--    |                    |             |
    //           |    |                    |             |
    //***********_****_********************_*************_****************
    addMenuItem('A', "print(Hello);",     (ACTION_FUNC) &Test::myFunc);
    addMenuItem('B', "Get a int Test",    (ACTION_FUNC) &Test::myFunc2);
    addMenuItem('C', "Get a float Test",  (ACTION_FUNC) &Test::myFunc3);
    addMenuItem('D', "Get a double Test", (ACTION_FUNC) &Test::myFunc4);
    addMenuItem('E', "Get a string Test", (ACTION_FUNC) &Test::myFunc5);
    addMenuItem('F', "Exit Program",      (ACTION_FUNC) &Test::myExit);

    //-------------------------------------------------------------------------------
    // This displays menu and handles user selection and executes our functions :-)
    // This never returns -- So, hopefully, one of your functions uses exitOK() 
    //-------------------------------------------------------------------------------
    mainMenu();
}

//-------------------------------------------------------------
// The following are our "Action Functions" -- 
// They are magically invoked by the DixieMenu base class
// that this Test class is derived from...
// 
// there are some useful functions in the DixieMenu base 
// class, such as; print() and dixieString() - which will 
// convert int, float, and double types into strings :-)
//  also user input functions...
// All std:cout and std::cin functions may be still used 
// if one so chooses however, the DixieMenu functions 
// are cleaner and provide more practical functionality  :-)
//-------------------------------------------------------------
void Test::myFunc()
{
    print2("Hello Y'all!!!");     // print2() does not print endl
    print2(" SUP???", TTY_GREEN); // print2() (and print()) can accept color parameters 
    newLine();                    // newLine() does: "cout << endl;" 
    newLine();
    print("yoooo");               // print() automatically prints endl and can accept color as well
    print("dixie bitches b like", TTY_MAGENTA);

    print("Version       = "+ getVersion());
    print("Serial Number = "+ getSerialNumber());

}

void Test::myFunc2()
{
    //        gets a user int - the prompt   min max
    int z    = userEnteredInt("Enter Value", 1,  10); 
    print("You entered: " + dixieString(z), TTY_RED);    
}

void Test::myFunc3()
{
    //      gets a user float - the prompt   min  max
    float z = userEnteredFloat("Enter Value",1.2, 10.1);
    print("You entered: " + dixieString(z), TTY_RED);    
}

void Test::myFunc4()
{
    //      gets a user double -  the prompt   min  max
    double z = userEnteredDouble("Enter Value",1.2, 10.1);
    print("You entered: " + dixieString(z));    // This one doesn't change color
}

void Test::myFunc5()
{
    //------- simply better than cout and cin :-)
    string z = userEnteredString("Enter String");
    print("You entered: " + z, TTY_RED);
}

void Test::myFunc6()
{
    //---- was a simple test for writeFile()
    string s = "Wrote this to testdata.dat\n";
    char buff[200];
    strcpy(buff, s.c_str());
    writeFile("testdata.dat",buff);
    print(s);
}

void Test::myExit()
{
    exitOK("Good Bye!"); // yayyy -- exit :-)
}

//-----------------------------------------------------------------
// Here's main() -- main is not part of the Test class but 
// main is needed to be the entry point for all running programs 
// (on linux, mac osx, and  windows operating systems) 
// It is for this reason main shoud be a minimal function :-)
// 
// 1) Creates the object we created for our application
// 2) Invoke start() (and passing argc and argv)
// 3) return(0) -- actually main will never return and 
//    one of our object's functions will perform an orderly exit :-) 
//------------------------------------------------------------------
int main(int argc, char **argv)
{   
    Test *test = new Test();    // We use "new' because we want this to be allocated memory
    test->start(argc, argv);    // the object will use exit() so there's no dangling pointers 
                                // to concern ourselves with :-)  
    return (0);                 // This return(0) will never happen -- it's just to make the 
                                // compiler happy :-)
}

