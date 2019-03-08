//-----------------------------------------------------------------------------
// CGIDiaper.h       Definition file for CGIDiaper.cpp
//-----------------------------------------------------------------------------
#ifndef CGIDIAPER_H
#define CGIDIAPER_H
#include <DixieApp.h>

#include <new>
#include <memory>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <fcntl.h>
#include <algorithm>
#include <functional>
#include <iterator>

#include <NameValue.h>
#include <FormFile.h>
//
//--------------------------------------------------
// CGIDiaper is the base class for any libdixie CGI  
// based applications.
//--------------------------------------------------
class CGIDiaper : public DixieApp
{
    private:
    string htmlData;
    string headerData;
    string postData;
    
    string serverSoftware;
    string serverName;
    string gatewayInterface;
    string serverProtocol;
    int    serverPort;
    string requestMethod;
    string documentRoot;
    string pathInfo;
    string pathTranslated;
    string scriptName;
    string queryString;
    string remoteHost;
    string remoteAddr;
    string authType;
    string remoteUser;
    string remoteIdent;
    string contentType;
    int    contentLength;
    string accept;
    string userAgent;
    string redirectRequest;
    string redirectURL;
    string redirectStatus;
    string referrer;
    string cookie;
    bool usingHTTPS;

    void   init(void);
    void   setSessionCookie(void);
    void   setConfigParams(void);
    void   createSession(void);
    void   closeSession(void);
    void   getEnvironment(void);
    string safeGetenv(const char *);
    bool   stringsAreEqual(string, string);
    bool   stringsAreEqual(string, string, size_t);
    char   hexToChar(char, char);
    string unescapeString(string);
    string extractBetween(string, string, string);
    void   parseFormInput(string);    
    void   parsePair(string);
    void   parseMIME(string);
    void   parseCookies(void);
    void   parseCookie(string);
    MultipartHeader parseHeader(string);
    
    public:
    
    Properties       config;    // Configuration properties for CGI
    Properties       session;   // User session data
    Properties       formEntry; // Form entry variables
    Queue<FormFile>  formFiles; // Uploaded files
    Queue<NameValue> cookies;   // Cookies...
    
    void   start(int, char **);
    void   redirect(string);
    void   startHtml(string);
    void   endHtml(void);
    void   addHtml(string);
    void   addHeader(string);
    
    virtual void   cgiResponse(void) = 0;
    virtual void   makeHeader(void);
    virtual string getConfPath(void);
    
    string getServerSoftware(void);
    string getServerName(void);
    string getGatewayInterface(void);
    string getServerProtocol(void);
    int    getServerPort(void);
    string getRequestMethod(void);
    string getDocumentRoot(void);
    string getPathInfo(void);
    string getPathTranslated(void);
    string getScriptName(void);
    string getQueryString(void);
    string getRemoteHost(void);
    string getRemoteAddr(void);
    string getAuthType(void);
    string getRemoteUser(void);
    string getRemoteIdent(void);
    string getContentType(void);
    int    getContentLength(void);
    string getAccept(void);
    string getUserAgent(void);
    string getRedirectRequest(void);
    string getRedirectURL(void);
    string getRedirectStatus(void);
    string getReferrer(void);
    string getCookie(void);
    bool   getUsingHTTPS(void);

    CGIDiaper();
};

#endif
