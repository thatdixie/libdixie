#include <DixieMenu.h>
#include <cstring>
#include "PhoneDatabase.h"

//------------------------------------------------
// Default data file name for phone database
//------------------------------------------------
string const PHONE_DATAFILE_NAME = "phonedata.dat";

class PhoneBookApp : public DixieMenu
{
    private:
    PhoneDatabase  *db;
    bool            saveFlag;
    
    public:
    void searchDatabase(void);
    void addContact(void);
    void updateContact(void);
    void removeContact(void);
    void saveDatabase(void);
    void loadDatabase(void);
    
    void   doExit(void);
    void   start(int, char **);
    string getDataFile(int, char **);
};


