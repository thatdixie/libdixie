#include "DixieTerminal.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <cassert>

using namespace std;
/***********************************************
 * @class Main
 * @brief Main is the main application class. It
 * derives from DixieTerminal which provides 
 * core functionality for terminal/command line
 * applications.
 * @details
 ***********************************************
 */
class Main : public DixieTerminal
{
    public:

    void start(int, char **);
    void test1(void);
    void test2(void);
    void test3(void);
};


