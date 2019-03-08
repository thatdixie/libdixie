#include "PhoneDatabase.h"

/**
 * Opens a Phone Book database
 *
 * @param string      -- the name of database file
 * @param DixieMenu * -- the application context
 * @return True if opened OK, or false if not.
 */
bool PhoneDatabase::open(string database, DixieApp *context)
{
    if(!this->isOpen)
    {	
    phoneData          = database;             // This is database file
    phoneHashTable     = new PhoneHashTable(); // This is the hashtable
    applicationContext = context;              // This points to parent app
    errorMessage       = "";                   // currently no errors
    if(!applicationContext->isFile(phoneData))
    {                                          // if there is currenty no data file then
	PhoneContact c;                        // create a contact
	string data ="";                       // and data string
	c.initDbRecord();                      // initialize dummy record 
	data = data + c.name +    ",";         // write record to datafile...
	data = data + c.nickname +",";
	data = data + c.phone    +",";
	data = data + c.email    +",";
	data = data + c.key1     +",";
	data = data + c.key2     +",";
	data = data + c.key3     +",";
	data = data + c.key4     +"\n";

        applicationContext->writeFile(phoneData, (char *)data.c_str());
    }
    this->isOpen       = true;                 // database is now open
    }
    return(true);
}

/**
 * Finds a record according to it's search key.
 *
 * @param  string       -- key The search key associated with record.
 * @return PhoneContact -- PhoneContact record
 * @throws exception    -- throws runtime exception if not found
 */
PhoneContact PhoneDatabase::searchPhoneBook(string key)
{
    if(!this->isOpen)
	throw std::runtime_error("Database not opened");
    //--------------------------------------
    // we're gonna make sure search keys are
    // always lowercase...
    //--------------------------------------
    string       s = this->toLowerCase(key);
    PhoneContact contact;
    try
    {
        contact = phoneHashTable->select(s);
    }
    catch(std::exception &e)
    {
	throw std::runtime_error(string(e.what()));	
    }	
    return(contact);
}

/**
 * Add a record into the database according to it's search key.
 *
 * @param PhoneContact -- The record to add to the database.
 * @return True if record was added successfully, or false if not.
 */
bool PhoneDatabase::addContact(PhoneContact record)
{
    //----------------------------------------------------------
    // failry simple -- 1) do not insert empty keys and
    //                  2) do not insert duplicate keys
    //----------------------------------------------------------
    if(record.key1 != "" && !phoneHashTable->hasKey(record.key1))
	phoneHashTable->insert(record.key1, record);
    if(record.key2 != "" && !phoneHashTable->hasKey(record.key2))
	phoneHashTable->insert(record.key2, record);
    if(record.key3 != "" && !phoneHashTable->hasKey(record.key3))
	phoneHashTable->insert(record.key3, record);
    if(record.key4 != "" && !phoneHashTable->hasKey(record.key4))
	phoneHashTable->insert(record.key4, record);
    
    return(true);
}
 
/**
 * Updates a record into the database.
 *
 * @param Phonecontact -- The record to update to the map.
 * @return bool        -- true if record was updated successfully, or 
 *                        false if not.
 */
bool PhoneDatabase::updateContact(PhoneContact record)
{
    phoneHashTable->update(toLowerCase(record.key1), record);
    phoneHashTable->update(toLowerCase(record.key2), record);
    phoneHashTable->update(toLowerCase(record.key3), record);
    phoneHashTable->update(toLowerCase(record.key4), record);
    return(true);
}


/**
 * Deletes a record from this map.
 *
 * @param Phonecontact -- The record to delete from the map.
 * @return bool        -- true if record was deleted successfully, or
 *                        false if not.
 */
bool PhoneDatabase::removeContact(PhoneContact record)
{
    phoneHashTable->remove(record.key1);
    phoneHashTable->remove(record.key2);
    phoneHashTable->remove(record.key3);
    phoneHashTable->remove(record.key4);
    return(true);
}


/**
 * loads database.
 *
 */
bool PhoneDatabase::load()
{
    if(!this->isOpen)                            // bugout if PhoneDatabase 
    {   this->errorMessage ="database not open"; // is not opened...
	return(false); 
    }
    //------------------------------------------------------
    // Reads phone book data file into a buffer...
    //------------------------------------------------------
    char *filedata = applicationContext->readFile(phoneData);
    
    if(!filedata)                                         // bugout if readFile()
    {   this->errorMessage ="could not open "+phoneData;  // failed..
	return (false);
    }
    //----------------------------------------------------
    // Parse contents of datafile and then attempt to
    // insert new records into hashMap...
    //----------------------------------------------------
    if(!parseInsert(filedata))
    {   this->errorMessage ="could not parse datafile";  // failed..
	return (false);
    }
    delete filedata; // We don't need this anymore 
    return(true);    // Okey-Dokie :-)
}

/**
 * Parses char buffer for valid datafile records then inserts 
 * the contents into phoneHashTable.
 *
 * @param char ** -- char buffer.
 * @return bool   -- True if records was inserted successfully, or false if not.
 */
bool PhoneDatabase::parseInsert( char *buffer)
{
    PhoneContact        contact;
    string              key1;
    string              key2;
    string              key3;
    string              key4;
    //----------------------------------------
    // First parse the buffer for records
    // converting char buffer to string and
    // creating a stringstream to get lines
    //----------------------------------------
    string       lineString;
    string       fileString = string(buffer);
    stringstream fileStream(fileString);
    //---------------------------------------------
    // and for each line file terminated with \n
    // we parse columns seperated by ','
    //---------------------------------------------
    while(getline(fileStream, lineString))
    {
        stringstream lineStream(lineString);	
        getline(lineStream, contact.name,    ',');
        getline(lineStream, contact.nickname,',');
        getline(lineStream, contact.phone,   ',');
        getline(lineStream, contact.email,   ',');
        getline(lineStream, contact.key1,    ',');
        getline(lineStream, contact.key2,    ',');
        getline(lineStream, contact.key3,    ',');
        getline(lineStream, contact.key4,    ',');
        //---------------------------------------
        // We now populate our hashtable
        // with lowercase versions of each
        // possiable key...
        //---------------------------------------
        key1 = toLowerCase(contact.key1);
        key2 = toLowerCase(contact.key2);
        key3 = toLowerCase(contact.key3);
        key4 = toLowerCase(contact.key4);	
        if(!phoneHashTable->hasKey(key1))
	    phoneHashTable->insert(key1, contact);
        if(!phoneHashTable->hasKey(key2))
	    phoneHashTable->insert(key2, contact);
        if(!phoneHashTable->hasKey(key3))
	    phoneHashTable->insert(key3, contact);
        if(!phoneHashTable->hasKey(key4))
	    phoneHashTable->insert(key4, contact);
    }
    return(true);
}

/**
 * Saves database to datafile.
 *
 */
bool PhoneDatabase::save()
{
    Queue<PhoneContact> *q = new Queue<PhoneContact>;
    PhoneHashTable      *h = new PhoneHashTable();
    PhoneContact         c;
    string               data = "";
    //------------------------------------
    // First get hashtable dump into q
    //------------------------------------
    phoneHashTable->dump(q);

    //------------------------------------
    // process each record...
    //-----------------------------------
    while(!q->isEmpty())
    {
	c = q->dequeue();
	//-------------------------------------------------
	// the hashtable has an entry for each key
	// we're only saving one...
	//-------------------------------------------------
	if(!h->hasKey(c.key1))
        {   //------------------------------------
	    // this is like #ifndef #define logic
	    //------------------------------------
	    h->insert(c.key1, c);
            //--------------------------------
	    // Form an ASCII data record...
	    //--------------------------------
            data = data + c.name +    ",";
	    data = data + c.nickname +",";
	    data = data + c.phone    +",";
	    data = data + c.email    +",";
	    data = data + c.key1     +",";
	    data = data + c.key2     +",";
	    data = data + c.key3     +",";
	    data = data + c.key4     +"\n";
	}
    }
    //----------------------------------------------------------
    // Write database...
    //----------------------------------------------------------
    applicationContext->writeFile(this->phoneData, (char *)data.c_str());

    delete q;    // done with this...
    delete h;    // and this.
    return(true);
}

/**
 * Converts string to lowercase 
 *
 * @param  string -- string to convert
 * @return string -- converted string 
 */
string PhoneDatabase::toLowerCase(string s)
{
    locale       loc; // we need this mystery object
    stringstream f;   // string streams are fun :-)
    for(string::size_type i=0; i < s.length(); i++)
	f << tolower(s[i], loc);  // put each char in stream

    return(f.str()); // rerurn our stream converted to new string 
}
 
/**
 * returns the errorMessage string 
 *
 * @return string -- this->errorMessage string 
 */
string PhoneDatabase::getErrorMessage()
{
    return(this->errorMessage); 
}

 
/**
 *  Default Constructor
 */
PhoneDatabase::PhoneDatabase()
{
    this->isOpen = false;
}

/**
 * Deconstructor
 */
PhoneDatabase::~PhoneDatabase()
{
    if(this->isOpen)
        delete phoneHashTable;
}

