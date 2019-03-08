#include "test.h"
#include <cstring>

void Test::start(int argc, char **argv)
{
    defaultProperties();
    config->open("test.dat", this);
    config->save();

    print("test test...");
    
    exitOK("Wrote test.dat...exitOK");
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

