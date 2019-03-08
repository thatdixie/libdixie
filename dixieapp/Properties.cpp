#include <NameValue.h>
#include <Properties.h>


/**
 * Opens a Properties database
 *
 * @param string     -- the name of database file
 * @param DixieApp * -- the application context
 * @return True if opened OK, or false if not.
 */
bool Properties::open(string database, DixieApp *context)
{
    if(!this->isOpen)
    {	
        propertiesFile     = database; // This is database file
        applicationContext = context;  // This points to parent app
        errorMessage       = "";       // currently no errors
        this->isOpen       = true;     // database is now open
    }
    return(true);
}

bool Properties::save()
{
    if(!this->isOpen)                            // bugout if Database 
    {   this->errorMessage ="database not open"; // is not opened...
	return(false); 
    }
    Queue<NameValue> *q = new Queue<NameValue>;
    NameValue         c;
    string            data = "";
    //------------------------------------
    // First get hashtable dump into q
    //------------------------------------
    hash.dump(q);

    //------------------------------------
    // process each record...
    //-----------------------------------
    while(!q->isEmpty())
    {
        c = q->dequeue();
        if(!(c.getValue() ==""))
            data = data +c.getName()+"="+c.getValue()+"\n";
    }
    //----------------------------------------------------------
    // Write database...
    //----------------------------------------------------------
    applicationContext->writeFile(this->propertiesFile, (char *)data.c_str());

    delete q;    // done with this...
    return(true);    
}

/**
 * loads a properties database.
 *
 */
bool Properties::load()
{
    if(!this->isOpen)                            // bugout if database 
    {   this->errorMessage ="database not open"; // is not opened...
	return(false); 
    }
    //------------------------------------------------------
    // Reads data file into a buffer...
    //------------------------------------------------------
    char *filedata = applicationContext->readFile(propertiesFile);
    
    if(!filedata)                                              // bugout if readFile()
    {   this->errorMessage ="could not open "+propertiesFile;  // failed..
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
bool Properties::parseInsert( char *buffer)
{
    NameValue nv;
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
    // we parse columns seperated by '='
    //---------------------------------------------
    while(getline(fileStream, lineString))
    {
	string nvName;
	string nvValue;
        stringstream lineStream(lineString);	
        getline(lineStream, nvName,   '=');
        getline(lineStream, nvValue,  '\n');
	//-------------------------------------
	// check values are not empty
	//-------------------------------------
	if(nvName != "" && nvValue != "")
	{    
            nv.setName(nvName);
	    nv.setValue(nvValue);
	    hash.insert(nvName, nv);
	}
    }
    return(true);
}


/**
 * Dump contents of Properties into a Queue of
 * NameValue pairs
 *
 * @param  void
 * @return Queue<NameValue> * -- caller deletes Q.
 */
Queue<NameValue> *Properties::dump()
{
    //------------------------------------
    // make a queue...
    //------------------------------------
    Queue<NameValue> *q = new Queue<NameValue>;
    //------------------------------------
    // get hashtable dump into q
    //------------------------------------
    hash.dump(q);
    //--------------------------------------
    // return the queue (callers delete q's)
    //--------------------------------------
    return(q);    
}


string Properties::get(string n)
{
    try
    {
        NameValue nv = hash.select(n);
        return(nv.getValue());
    }
    catch(std::exception &e)
    {
	return "";
    }
}

int Properties::getInt(string n)
{
    try
    {
        NameValue nv = hash.select(n);
        return(nv.intValue());
    }
    catch(std::exception &e)
    {
	return 0;
    }
}

char Properties::getChar(string n)
{
    try
    {
        NameValue nv = hash.select(n);
        return(nv.charValue());
    }
    catch(std::exception &e)
    {
	return 0;
    }
}

short Properties::getShort(string n)
{
    try
    {
        NameValue nv = hash.select(n);
        return(nv.shortValue());
    }
    catch(std::exception &e)
    {
	return 0;
    }
}

long Properties::getLong(string n)
{
    try
    {
        NameValue nv = hash.select(n);
        return(nv.longValue());
    }
    catch(std::exception &e)
    {
	return 0;
    }
}

float Properties::getFloat(string n)
{
    try
    {
        NameValue nv = hash.select(n);
        return(nv.floatValue());
    }
    catch(std::exception &e)
    {
	return 0.0;
    }
}

double Properties::getDouble(string n)
{
    try
    {
        NameValue nv = hash.select(n);
        return(nv.floatValue());
    }
    catch(std::exception &e)
    {
	return 0;
    }
}

bool Properties::getBool(string n)
{
    try
    {
        NameValue nv = hash.select(n);
        return(nv.boolValue());
    }
    catch(std::exception &e)
    {
	return false;
    }
}


void Properties::put(string n, string v)
{
    NameValue nv(n,v);
    try
    {   //-----------------------------------
	// if the hash entry already exists
        // we update that entry...
	//-----------------------------------
        NameValue t = hash.select(n);
	if(t.getName() == nv.getName())
        {
	    hash.update(n,nv);
        }
        else
	{
	    throw std::runtime_error("hash entry empty");	    
	}
    }
    catch(std::exception &e)
    {   //-------------------------------
	// we add new hash entry
	// only if its not there already
	//--------------------------------
        hash.insert(n, nv);
    }
}



