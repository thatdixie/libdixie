
/*
*******************************************************************************************
*/
#include "PhoneBookApp.h"

void PhoneBookApp::start(int argc, char **argv)
{
    //-------------------------------------------
    // Here would be a good place to do things 
    // with argc and argv if you needed to :-)
    //-------------------------------------------
    //
    //--------------------------------------------
    // So, we start with opening our database...
    // and bugging out if we can't find datafile
    //--------------------------------------------
    saveFlag = false;
    string datafile = getDataFile(argc, argv);
    db = new PhoneDatabase();
    if(!db->open(datafile, this))
	errorExit("***ERROR with datafile:"+datafile+" error message="+db->getErrorMessage(), -1);
    //-------------------------
    // load initial database
    //-------------------------
    db->load();

    //-------------------------------------------
    // Sets the Menu Title -- simple enough :-)
    //-------------------------------------------
    setMenuTitle("Phone Book Version 1.0");

    //------------------------------------------------------------------------------
    // Here we create our Menu:
    //------------------------------------------------------------------------------
    addMenuItem('1', "Search Phone Book",(ACTION_FUNC) &PhoneBookApp::searchDatabase);
    addMenuItem('2', "Add Contact",      (ACTION_FUNC) &PhoneBookApp::addContact);
    addMenuItem('3', "Update Contact",   (ACTION_FUNC) &PhoneBookApp::updateContact);
    addMenuItem('4', "Remove Contact",   (ACTION_FUNC) &PhoneBookApp::removeContact);
    addMenuItem('5', "Save Database",    (ACTION_FUNC) &PhoneBookApp::saveDatabase);
    addMenuItem('6', "Load Database",    (ACTION_FUNC) &PhoneBookApp::loadDatabase);
    addMenuItem('X', "Exit Program",     (ACTION_FUNC) &PhoneBookApp::doExit);

    //-------------------------------------------------------------------------------
    // This displays menu and handles user selection and executes our functions :-)
    // This never returns -- So, hopefully, one of your functions uses exitOK() 
    //-------------------------------------------------------------------------------
    mainMenu();
}

//-------------------------------------------------------------
// The following are our "Action Functions" -- 
// They are magically invoked by the DixieMenu base class
// that this PhoneBookApp class is derived from...
// 
// there are some useful functions in the DixieMenu base 
// class, such as; print() and dixieString() - which will 
// convert int, float, and double types into strings :-)
//  also user input functions...
// All std:cout and std::cin functions may be still used 
// if one so chooses however, the DixieMenu functions 
// are cleaner and provide more practical functionality  :-)
//-------------------------------------------------------------

/**
 * Search the database for a record.
 */
void PhoneBookApp::searchDatabase()
{
    string       key="";
    PhoneContact contact;
    bool         notDone = true;
    do
    {
        key = userEnteredString("Please enter search key");
        try
        {
            contact = db->searchPhoneBook(key);	
	    print("==========");
	    print("Name     :"+contact.name);
	    print("Nickname :"+contact.nickname);
	    print("Phone    :"+contact.phone);
	    print("Email    :"+contact.email);
	}
        catch(std::exception &e)
        {
	    print("No record found for "+key, TTY_RED);
        }
        if(this->noThankYou("Would you like to do another search?"))
	    notDone = false;
	newLine();
    }while(notDone);

    return;
}

/**
 * Add a contact (PhoneContact) to database.
 */
void PhoneBookApp::addContact()
{
    PhoneContact c;
    c.name     = userEnteredString("Enter full name for contact");
    c.nickname = userEnteredString("Enter nickname for "+c.name);
    c.phone    = userEnteredString("Enter phone number for "+c.name);
    c.email    = userEnteredString("Enter email for "+c.name);
    c.key1     = userEnteredString("Enter search key to find "+c.name);
    if(this->yesPlease("Would you like to enter a second search key?"))
    {   c.key2= userEnteredString("Enter search key to find "+c.name);
        if(this->yesPlease("Would you like to enter a third search key?"))
	{   c.key3= userEnteredString("Enter search key to find "+c.name);
            if(this->yesPlease("Would you like to enter a forth search key?"))
                c.key4= userEnteredString("Enter search key to find "+c.name);
        }
    }
    //-------------------
    // Add contact
    //-------------------
    db->addContact(c);
    print("Contact "+c.name+" added", TTY_RED);
    saveFlag=true;
    return;
}

/**
 * Update a contact (PhoneContact) in database.
 */
void PhoneBookApp::updateContact()
{
    saveFlag        =false;
    string       key="";
    PhoneContact c;
    //------------------------------------------------
    // First find record to be updated...
    //------------------------------------------------
    key = userEnteredString("Please enter search key");
    try
    {
        c= db->searchPhoneBook(key);	
    }
    catch(std::exception &e)
    {
        print("No record found for "+key, TTY_RED);
        return;
    }
    //--------------------------------------------------------------
    // Update contact record data...
    //--------------------------------------------------------------
    if(this->yesPlease("would you like to modify full name "+c.name+"?"))
	c.name = userEnteredString("Enter full name");
    if(this->yesPlease("would you like to modify nickname "+c.nickname+"?"))
	c.nickname = userEnteredString("Enter new nickname");
    if(this->yesPlease("would you like to modify phone number "+c.phone+"?"))
	c.phone = userEnteredString("Enter new phone number");
    if(this->yesPlease("would you like to modify email "+c.email+"?"))
        c.email = userEnteredString("Enter new email");
    //----------------------------
    // Update database...
    //----------------------------
    db->updateContact(c);
    print("Contact "+c.name+" updated", TTY_RED);
    saveFlag=true;
    return;
}

/**
 * Remove a contact (PhoneContact) from database.
 */
void PhoneBookApp::removeContact()
{
    saveFlag        =false;
    string       key="";
    PhoneContact c;
    //------------------------------------------------
    // First find record to be removed...
    //------------------------------------------------
    key = userEnteredString("Please enter search key");
    try
    {
        c= db->searchPhoneBook(key);	
	print("==========");
	print("Name     :"+c.name);
	print("Nickname :"+c.nickname);
	print("Phone    :"+c.phone);
	print("Email    :"+c.email);
    }
    catch(std::exception &e)
    {
        print("No record found for "+key, TTY_RED);
        return;
    }
    if(this->yesPlease("would you like to remove "+c.name+"?"))
    {   //----------------------------
        // Update database...
        //----------------------------
        db->removeContact(c);
        print("Contact "+c.name+" removed", TTY_RED);
        saveFlag=true;
    }
    return;
}

/**
 * Save the Phone Book database.
 */
void PhoneBookApp::saveDatabase()
{
    if(db->save())
        print("Phone database updated", TTY_RED); 
    else
        print("***ERROR -- Could not update database!", TTY_RED);    
    //-----------------------------------------
    // set this in each case casue you
    // still need to exit if save failed :-)
    //-----------------------------------------
    saveFlag=false;
}

/**
 * Load the Phone Book database.
 */
void PhoneBookApp::loadDatabase()
{
    if(db->load())
        print("Phone database refreshed and loaded", TTY_RED); 
    else
        print("***ERROR -- Could not load database!", TTY_RED);

    saveFlag=false;
}

/**
 * Exit the Phone Book application.
 *
 * Checks if database needs to be saved 
 * before allowing exit.
 */
void PhoneBookApp::doExit()
{
    //----------------------------------
    // check if update or add was done.
    //----------------------------------
    if(saveFlag)
    {
	print("Please save database before exit",TTY_RED);
	return;
    }
    exitOK("Good Bye!"); // yayyy -- exit :-)
}

/**
 * Get the database datafile.
 * 
 * @param  int     -- count number of command line arguments
 * @param  char ** -- array of c-string arguments 
 * @return string  -- the datafile filename.
 */
string PhoneBookApp::getDataFile(int count, char **arg)
{
    string filename = PHONE_DATAFILE_NAME;

    if(count > 2)
    {
        if(string(arg[1]) == "-f")
	    filename = arg[2];
    }
    return(filename);
}


//-----------------------------------------------------------------
// Here's main() -- main is not part of the PhoneBookApp class but 
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
    PhoneBookApp *phoneBook = new PhoneBookApp(); // We use "new' because we want this to be allocated memory
    phoneBook->start(argc, argv);                 // the object will use exit() so there's no dangling pointers 
                                                  // to concern ourselves with :-)  
    return (0);                                   // This return(0) will never happen -- it's just to make the 
                                                  // compiler happy :-)
}

