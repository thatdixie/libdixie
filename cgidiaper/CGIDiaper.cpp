/*
******************************************************************************************
Title:       CGIDiaper.cpp
Author:      Megan Williams

Description: Implementation file for CGIDiaper class for the dixielib library. 
*******************************************************************************************
*/
#include "CGIDiaper.h"


//-------------------------------------------------------------------
// FUNCTION: start
//
// PURPOSE:
//
// INPUT:    int argc, char **argv
// RETURN:   N/A
//-------------------------------------------------------------------
void CGIDiaper::start(int argc, char **argv)
{
    char *content;
    int  len;
    
    init();
    //----------------------------------
    // First get the CGI environment...
    //----------------------------------
    getEnvironment();
    //---------------------------------
    // load configuration properties...
    //---------------------------------
    config.open(getConfPath()+getScriptName()+".conf", this);
    if(!config.load())
    {
	setConfigParams();
    }
    //---------------------------------------
    // if this is a post request we gotta
    // read-in all the content and vars...
    //---------------------------------------
    if (getRequestMethod() == "post" || getRequestMethod() == "POST")
    {   len = getContentLength();
	if(len > 0)
        {   content = new char[len];
	    cin.read(content, len);
	    postData = string(content, len);
            delete content;
	    parseFormInput(postData);
	}
    }
    else
    {   //-------------------------------
	// for GET requests we parse the
	// QUERY STRING...
	//-------------------------------
        parseFormInput(getQueryString());
    }

    createSession();// create/retrieve a user session based on cookie & config properties 
    makeHeader();   // call virtual function to set page <head></head> information
    cgiResponse();  // call virtual function to render webpage or redirect
    closeSession(); // save session information and close...
    exit(0);        // exit :) 
}

string CGIDiaper::getServerSoftware()
{
    return(serverSoftware);
}

string CGIDiaper::getServerName()
{
    return(serverName);
}

string CGIDiaper::getGatewayInterface()
{
    return(gatewayInterface);
}

string CGIDiaper::getServerProtocol()
{
    return(serverProtocol);
}

int    CGIDiaper::getServerPort()
{
    return(serverPort);
}

string CGIDiaper::getRequestMethod()
{
    return(requestMethod);
}

string CGIDiaper::getDocumentRoot()
{
    return(documentRoot);
}

string CGIDiaper::getPathInfo()
{
    return(pathInfo);
}

string CGIDiaper::getPathTranslated()
{
    return(pathTranslated);
}

string CGIDiaper::getScriptName()
{
    return(scriptName);
}

string CGIDiaper::getQueryString()
{
    return(queryString);
}

string CGIDiaper::getRemoteHost()
{
    return(remoteHost);
}

string CGIDiaper::getRemoteAddr()
{
    return(remoteAddr);
}

string CGIDiaper::getAuthType()
{
    return(authType);
}

string CGIDiaper::getRemoteUser()
{
    return(remoteUser);
}

string CGIDiaper::getRemoteIdent()
{
    return(remoteIdent);
}

string CGIDiaper::getContentType()
{
    return(contentType);
}

int    CGIDiaper::getContentLength()
{
    return(contentLength);
}

string CGIDiaper::getAccept()
{
    return(accept);
}

string CGIDiaper::getUserAgent()
{
    return(userAgent);
}

string CGIDiaper::getRedirectRequest()
{
    return(redirectRequest);
}

string CGIDiaper::getRedirectURL()
{
    return(redirectURL);
}

string CGIDiaper::getRedirectStatus()
{
    return(redirectStatus);
}

string CGIDiaper::getReferrer()
{
    return(referrer);
}

string CGIDiaper::getCookie()
{
    return(cookie);
}

bool   CGIDiaper::getUsingHTTPS()
{
    return(usingHTTPS);
}


//--------------------------------------------------------
// Get CGI goo...
//--------------------------------------------------------
void CGIDiaper::getEnvironment()
{
  serverSoftware  = safeGetenv("SERVER_SOFTWARE");
  serverName 	  = safeGetenv("SERVER_NAME");
  gatewayInterface= safeGetenv("GATEWAY_INTERFACE");
  serverProtocol  = safeGetenv("SERVER_PROTOCOL");

  string port 	  = safeGetenv("SERVER_PORT");
  serverPort 	  = atoi(port.c_str());

  requestMethod   = safeGetenv("REQUEST_METHOD");
  documentRoot    = safeGetenv("DOCUMENT_ROOT");
  pathInfo 	  = safeGetenv("PATH_INFO");
  pathTranslated  = safeGetenv("PATH_TRANSLATED");
  scriptName 	  = safeGetenv("SCRIPT_NAME");
  queryString 	  = safeGetenv("QUERY_STRING");
  remoteHost 	  = safeGetenv("REMOTE_HOST");
  remoteAddr 	  = safeGetenv("REMOTE_ADDR");
  authType 	  = safeGetenv("AUTH_TYPE");
  remoteUser 	  = safeGetenv("REMOTE_USER");
  remoteIdent 	  = safeGetenv("REMOTE_IDENT");
  contentType 	  = safeGetenv("CONTENT_TYPE");

  string length   = safeGetenv("CONTENT_LENGTH");
  contentLength   = atoi(length.c_str());

  accept 	  = safeGetenv("HTTP_ACCEPT");
  userAgent 	  = safeGetenv("HTTP_USER_AGENT");
  redirectRequest = safeGetenv("REDIRECT_REQUEST");
  redirectURL 	  = safeGetenv("REDIRECT_URL");
  redirectStatus  = safeGetenv("REDIRECT_STATUS");
  referrer 	  = safeGetenv("HTTP_REFERER");
  cookie 	  = safeGetenv("HTTP_COOKIE");
  usingHTTPS      = (getenv("HTTPS") != 0);
}

//-------------------------------------------------
// Get an environment variable
//-------------------------------------------------
string CGIDiaper::safeGetenv(const char *varName)
{
  char *var = getenv(varName);
  return (var == 0) ? "" : var;
}

//---------------------------------------------------------------------
// case-insensitive string comparison
// This code based on code from 
// "The C++ Programming Language, Third Edition" by Bjarne Stroustrup
//---------------------------------------------------------------------
bool CGIDiaper::stringsAreEqual(string s1, string s2)
{
    string::const_iterator p1 = s1.begin();
    string::const_iterator p2 = s2.begin();
    string::const_iterator l1 = s1.end();
    string::const_iterator l2 = s2.end();

    while(p1 != l1 && p2 != l2)
    {
        if(toupper(*(p1++)) != toupper(*(p2++)))
            return false;
    }
    return (s2.size() == s1.size()) ? true : false;
}

//---------------------------------------------------------------------
// case-insensitive string comparison
// This code based on code from 
// "The C++ Programming Language, Third Edition" by Bjarne Stroustrup
//---------------------------------------------------------------------
bool CGIDiaper::stringsAreEqual(string s1, string s2, size_t n)
{
    string::const_iterator p1 = s1.begin();
    string::const_iterator p2 = s2.begin();
    bool good = (n <= s1.length() && n <= s2.length());
    string::const_iterator l1 = good ? (s1.begin() + n) : s1.end();
    string::const_iterator l2 = good ? (s2.begin() + n) : s2.end();

    while(p1 != l1 && p2 != l2)
    {
        if(toupper(*(p1++)) != toupper(*(p2++)))
            return false;
    }
  
    return good;
}

char CGIDiaper::hexToChar(char first, char second)
{
    char digit;
    digit = (first >= 'A' ? ((first & 0xDF) - 'A') + 10 : (first - '0'));
    digit *= 16;
    digit += (second >= 'A' ? ((second & 0xDF) - 'A') + 10 : (second - '0'));
    return digit;
}

string CGIDiaper::unescapeString(string src)
{
    string result;
    string::const_iterator iter;
    char c;

    for(iter = src.begin(); iter != src.end(); ++iter)
    {
        switch(*iter)
        {
            case '+':
            result.append(1, ' ');
            break;
            case '%':
            // assume well-formed input
            // ensure evaluation order for hexToChar
            c = *++iter;
            result.append(1, hexToChar(c, *(++iter)));
            break;
            default:
            result.append(1, *iter);
            break;
        }
    }
    return result;
}

// locate data between separators, and return it
string CGIDiaper::extractBetween(string data, string separator1, string separator2)
{
    string result;
    unsigned int start, limit;
  
    start = data.find(separator1, 0);

    if(start != string::npos)
    {
        start += separator1.length();
        limit = data.find(separator2, start);
        if(limit != string::npos)
            result = data.substr(start, limit - start);
    }
 
    return result;
}


void CGIDiaper::parseFormInput(string data)
{
    string env 	= getContentType();
    string cType= "multipart/form-data";

    if(stringsAreEqual(cType, env, cType.length()))
    {
        // Find out what the separator is
        string bType         = "boundary=";
	string::size_type pos= env.find(bType);

        // generate the separators
        string sep = env.substr(pos + bType.length());
        sep.append("\r\n");
        sep.insert(0, "--");

        string sep2 = env.substr(pos + bType.length());
        sep2.append("--\r\n");
        sep2.insert(0, "--");

        // Find the data between the separators
	string::size_type  start  = data.find(sep);
	string::size_type  sepLen = sep.length();

        pos = 0;
	string::size_type oldPos = start + sepLen;

        while(true)
	{
            pos = data.find(sep, oldPos);

            // If sep wasn't found, the rest of the data is an item
            if(pos == string::npos)
	        break;
            // parse the data
            parseMIME(data.substr(oldPos, pos - oldPos));
            // update position
            oldPos = pos + sepLen;
        }

        // The data is terminated by sep2
        pos = data.find(sep2, oldPos);
        // parse the data, if found
        if(pos != string::npos)
	{
            parseMIME(data.substr(oldPos, pos - oldPos));
        }
    }
    else if(! data.empty())
    {
	string::size_type pos   = 0;
        string::size_type oldPos= 0;

        while(true)
	{
            // find the '&' separating a name=value pairs
            pos = data.find_first_of("&", oldPos);
            // if no '&' was found, the rest of the string is a pair
            if(pos == string::npos)
	    {
	        parsePair(data.substr(oldPos));
	        break;
            }
      
            // otherwise, parse the name=value pair
            parsePair(data.substr(oldPos, pos - oldPos));
      
            // update position
            oldPos = pos + 1;
        }
    }
}

void CGIDiaper::parseCookies()
{
    string data = getCookie();

    if(! data.empty())
    {
        string::size_type pos 	= 0;
        string::size_type oldPos= 0;

        while(true)
        {
            // find the ';' terminating a name=value pair
            pos = data.find(";", oldPos);

            // if no ';' was found, the rest of the string is a single cookie
            if(pos == string::npos)
	    {
	        parseCookie(data.substr(oldPos));
	        return;
            }

            // otherwise, the string contains multiple cookies
            // extract it and add the cookie to the list
            parseCookie(data.substr(oldPos, pos - oldPos));
      
            // update pos (+1 to skip ';')
            oldPos = pos + 1;
        }
    }
}

void CGIDiaper::parseCookie(string data)
{
    // find the '=' separating the name and value
    string::size_type pos = data.find("=", 0);

    // if no '=' was found, return
    if(pos == string::npos)
        return;

    // skip leading whitespace - " \f\n\r\t\v"
    string::size_type wscount = 0;
    string::const_iterator data_iter;
  
    for(data_iter = data.begin(); data_iter != data.end(); ++data_iter,++wscount)
        if(isspace(*data_iter) == 0)
            break;			
  
    // unescape the data, and add to the cookie list
    string name 	= unescapeString(data.substr(wscount, pos - wscount));
    string value 	= unescapeString(data.substr(++pos));

    cookies.enqueue(NameValue(name, value));
}


MultipartHeader CGIDiaper::parseHeader(string data)
{
    string disposition;
    disposition = extractBetween(data, "Content-Disposition: ", ";");
  
    string name;
    name = extractBetween(data, "name=\"", "\"");
  
    string filename;
    filename = extractBetween(data, "filename=\"", "\"");

    string cType;
    cType = extractBetween(data, "Content-Type: ", "\r\n\r\n");

    // This is hairy: Netscape and IE don't encode the filenames
    // The RFC says they should be encoded, so I will assume they are.
    filename = unescapeString(filename);

    return MultipartHeader(disposition, name, filename, cType);
}

void CGIDiaper::parsePair(string data)
{
    // find the '=' separating the name and value
    string::size_type pos = data.find_first_of("=", 0);

    // if no '=' was found, return
    if(pos == string::npos)
        return;
  
    // unescape the data, and add to the form entry list
    string name = unescapeString(data.substr(0, pos));
    string value= unescapeString(data.substr(++pos, string::npos));
  
    formEntry.put(name, value);
    return;
}

void CGIDiaper::parseMIME(string data)
{
    // Find the header
    string end = "\r\n\r\n";
    string::size_type headLimit = data.find(end, 0);
  
    // Detect error
    if(headLimit == string::npos)
        return;

    // Extract the value - there is still a trailing CR/LF to be subtracted off
    string::size_type valueStart = headLimit + end.length();
    string value = data.substr(valueStart, data.length() - valueStart - 2);

    // Parse the header - pass trailing CR/LF x 2 to parseHeader
    MultipartHeader head = parseHeader(data.substr(0, valueStart));

    if(head.getFilename().empty())
        formEntry.put(head.getName(), value);
    else
    {
        formFiles.enqueue(FormFile(head.getName(), 
				   head.getFilename(), 
				   head.getContentType(), 
				   value));
    }
}

void CGIDiaper::setConfigParams()
{
    if(config.get("session_timeout") == "")
        config.put("session_timeout", "600");         // 10 minute session by default

    if(config.get("session_dir") == "")
        config.put("session_dir", getConfPath()+"/"); // sessions in docroot not good...

    if(config.get("domain") == "")
        config.put("domain", ".thatdixie.com");       // assume cookie domain...

    if(config.get("cookie_name") == "")
        config.put("cookie_name", "dixie-session");   // assume cookie name...
}

void CGIDiaper::createSession()
{
    bool   noSessionFound = true;
    
    //------------------------------
    // first try and find cookies...
    //------------------------------
    parseCookies();

    if(cookies.isEmpty())
    {   //----------------------------
	// No cookie found so
	// we create a session cookie
        //----------------------------
        setSessionCookie();
    }
    else
    {   //------------------------------
	// At least one cookie found so
	// we try and find session...
	//-------------------------------
        while(!cookies.isEmpty())
	{
	    NameValue nv = cookies.dequeue();
	    if(isFile(config.get("session_dir")+nv.getValue()+".txt"))
	    {   //--------------------------------------
		// Load current user session...
		//--------------------------------------
                session.open(config.get("session_dir")+nv.getValue()+".txt", this);
                session.load();
                session.put("session_name", nv.getValue());
                noSessionFound = false;
		break;
	    }
	}
	if(noSessionFound)
        {   //--------------------------------------------------
	    // There's a cookie but it's not the cookie I want
            // so, we're gonna make another cookie...
            //---------------------------------------------------
	    setSessionCookie();
	}
    }
}

void CGIDiaper::setSessionCookie()
{
    string name;
    string domain;
    string cname;
    string expire;

    setConfigParams();          // set params that may or may not been set :-)
    name    = randomString(10); // a random string xxxxxxxxxx.txt will be cookie session
    domain  = config.get("domain");
    cname   = config.get("cookie_name");
    expire  = config.get("session_timeout");
    //--------------------------
    // Set the Cookie in browser
    //--------------------------
    print("Set-Cookie: "+cname+"="+name+"; Max-Age="+expire+"; Domain="+domain+"; Path=/;"); 
    session.put("session_name", name);
}



void CGIDiaper::closeSession()
{
    session.open(config.get("session_dir")+session.get("session_name")+".txt", this);
    session.save();
}

void CGIDiaper::redirect(string location)
{
    print("Location: "+location+"\n\n");
}


void CGIDiaper::startHtml(string title)
{
    addHtml("Content-Type: text/html\n");
    addHtml("<!DOCTYPE html>");
    addHtml("<html>");
    addHtml("<head>");
    addHtml("<title>"+title+"</title>");
    if(headerData != "")
        addHtml(headerData);
    addHtml("</head>");
    addHtml("<body>");
    return;
}

void CGIDiaper::endHtml()
{
    addHtml("</body>");
    addHtml("</html>");

    print(htmlData+"\n");
    return;
}

void CGIDiaper::addHtml(string s)
{
    htmlData = htmlData + s +"\n";
    return;
}

void CGIDiaper::init()
{
    htmlData   = "";
    headerData ="";
    
    return;
}

void CGIDiaper::addHeader(string s)
{
    headerData = headerData + s +"\n";
    return;
}

void CGIDiaper::makeHeader()
{
    // virtual function -- implement and 
    // use addHeader() to add links and metadata
    //-----------------------------------------------
    return;
}

string CGIDiaper::getConfPath()
{
    return(".");
}

FormFile::FormFile()
{

}

FormFile::FormFile(string name,
	           string filename,
	           string dataType,
                   string data)
{
    fName     = name;
    fFilename = filename;
    fDataType = dataType;
    fData     = data;
}

MultipartHeader::MultipartHeader(string disposition,
		                 string name,
		                 string filename,
		                 string cType)
{
    fContentDisposition = disposition;
    fName               = name;
    fFilename           = filename;
    fContentType        = cType;
}

//-----------------------------------------------------------
// FUNCTION: CGIDiaper()
// PURPOSE: Default constructor
//-----------------------------------------------------------
CGIDiaper::CGIDiaper()
{

}
