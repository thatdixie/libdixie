/*
*******************************************************************************************
*/
#include "test.h"


void Test::cgiResponse()
{
    startHtml("test.cgi");
    cgiSummary();
    cgiGoo();
    endHtml();
}

void Test::cgiSummary()
{
    if(formEntry.getInt("state") == 1)
        doState1();
    else if (formEntry.getInt("state") == 2) 
        doState2();
    else if(formFiles.isEmpty())
        redirect("http://thatdixiebitch/test1.html");
    else
	doState2();
    
    return;
}

void Test::doState1()
{
    //---------------------------------------------
    // if user did not enter first and last names
    // then redirect back to form
    //---------------------------------------------
    string first = formEntry.get("first_name");
    string last  = formEntry.get("last_name");
    if(first==""  ||  last== "")
    {
	redirect("http://thatdixiebitch/test1.html");
        return;
    }
    //----------------------------------------
    // Save first and last name in session
    //----------------------------------------
    session.put("first_name", first);
    session.put("last_name",  last);
    
    addHtml("<h2>Hello "+first+" "+last+"!<h2>" );
    addHtml("<h2>The current session timeout is "+config.get("session_timeout")+" seconds</h2>" );
    addHtml("<h2>The session dir is "+config.get("session_dir")+"</h2>" );
    addHtml("<h2>The session is "+config.get("session_dir")+session.get("session_name")+".txt</h2>" );
    addHtml("<h2><a href=http://thatdixiebitch/test2.html>CLICK HERE</a> to contine to next test...</h2>" );
    cgiCounter();
}

void Test::doState2()
{
    addHtml("<h2>The session dir is "+config.get("session_dir")+"</h2>" );
    addHtml("<h2>"+config.get("session_dir")+session.get("session_name")+".txt</h2>" );

    //-------------------------------------------------
    // We keep fitst_name and last_name in session...
    //-------------------------------------------------
    string first = session.get("first_name");
    string last  = session.get("last_name");
    /*    if(first==""  ||  last== "")
    {
        redirect("http://thatdixiebitch/test1.html");
        return;
    }
    */
    //---------------------------------------------
    // Welcome back first_name last_name :-)
    // here we check for possible file upload
    //---------------------------------------------
    addHtml("<h2>Welcome BACK "+first+" "+last+"!<h2>" );
    if(!formFiles.isEmpty())
    {
        addHtml("<h2>File upload found!</h2>");
        FormFile ff = formFiles.dequeue();
	string name     = ff.getName();
	string filename = ff.getFilename();
	string fileType = ff.getDataType();
	int    len      = ff.getDataLength();
        addHtml("<h2>name="+name+"</h2>");
        addHtml("<h2>filename="+filename+"</h2>");
	addHtml("<h2>fileType="+fileType+"</h2>");
	addHtml("<h2>file length="+dixieString(len)+"</h2>");
        string data = ff.getData();
	
        writeFile("./upload/"+filename, (char *)data.c_str(), len);

        addHtml("<h2>Saved to upload directory and viewable <a href=http://thatdixiebitch/upload/"+filename+">HERE</a></h2>");
    }

    addHtml("<h2><a href=http://thatdixiebitch/test1.html>CLICK HERE</a> to contine to next test -- or"); 
    addHtml(" reload this page and watch the counter go up </h2>" );
    cgiCounter();
}

void Test::cgiCounter()
{
    //-----------------------------------
    // get current session counter...
    //------------------------------------
    int count = session.getInt("count");
    
    addHtml("<h2>The running session counter for this CGI is "+dixieString(count)+"<h2>");

    //--------------------------------------
    // Increment counter and store it back
    // to the current session...
    //--------------------------------------
    count++;
    session.put("count", dixieString(count));
}



void Test::cgiGoo()
{
    addHtml("<h1>CGI GOO</h1>");
    addHtml("<table border=\"1\" cellspacing=\"0\" cellpadding=\"10\"> ");

    addHtml("<tr>"); addHtml("<td>"); addHtml("SERVER SOFTWARE"); addHtml("</td>");
    addHtml("<td>"); addHtml(getServerSoftware()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("SERVER NAME"); addHtml("</td>");
    addHtml("<td>"); addHtml(getServerName()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("GATEWAY"); addHtml("</td>");
    addHtml("<td>"); addHtml(getGatewayInterface()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("PROTOCOL"); addHtml("</td>");
    addHtml("<td>"); addHtml(getServerProtocol()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("PORT"); addHtml("</td>");
    addHtml("<td>"); addHtml(dixieString(getServerPort()) ); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REQUEST METHOD"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRequestMethod()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("PATH INFO"); addHtml("</td>");
    addHtml("<td>"); addHtml(getPathInfo()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("PATH TRANSLATED"); addHtml("</td>");
    addHtml("<td>"); addHtml(getPathTranslated()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("SCRIPT-NAME"); addHtml("</td>");
    addHtml("<td>"); addHtml(getScriptName()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("QUERY STRING"); addHtml("</td>");
    addHtml("<td>"); addHtml(getQueryString()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("REMOTE HOST"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRemoteHost()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REMOTE ADDRESS"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRemoteAddr()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("AUTH TYPE"); addHtml("</td>");
    addHtml("<td>"); addHtml(getAuthType()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("REMOTE USER"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRemoteUser()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("REMOTE IDENT"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRemoteIdent()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("CONTENT TYPE"); addHtml("</td>");
    addHtml("<td>"); addHtml(getContentType()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("CONTENT LENGTH"); addHtml("</td>");
    addHtml("<td>"); addHtml(dixieString(getContentLength())); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("ACCEPT"); addHtml("</td>");
    addHtml("<td>"); addHtml(getAccept()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("USER AGENT"); addHtml("</td>");
    addHtml("<td>"); addHtml(getUserAgent()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REDIRECT REQUEST"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRedirectRequest()); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("<tr>"); addHtml("<td>"); addHtml("REDIRECT URL"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRedirectURL()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REDIRECT STATUS"); addHtml("</td>");
    addHtml("<td>"); addHtml(getRedirectStatus()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("REFERRER"); addHtml("</td>");
    addHtml("<td>"); addHtml(getReferrer()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("COOKIE"); addHtml("</td>");
    addHtml("<td>"); addHtml(getCookie()); addHtml("</td>"); addHtml("</tr>");

    addHtml("<tr>"); addHtml("<td>"); addHtml("USING HTTPS"); addHtml("</td>");
    addHtml("<td>"); addHtml((getUsingHTTPS() ? "yes" :"no")  ); addHtml("</td>"); addHtml("</tr>");
    
    addHtml("</table>");
    addHtml("<br/>");
}

/*
void Test::makeHeader()
{
    addHeader("<link rel=\"stylesheet\" href=\"css/layout.css\" type=\"text/css\" />");
    addHeader("<meta name=\"keywords\" content=\"Hunter Collage, C++, Computer Science Major, Megan Williams\" />");
    addHeader("<meta name=\"description\" content=\"Dixie Bitches in da house holla!\" />");
}
*/

string Test::getConfPath()
{
    return(CONF_DIR);
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
    Test *test = new Test();          // We use "new' because we want this to be allocated memory
    test->start(argc, argv);          // the object will use exit() so there's no dangling pointers 
    return (0);                       // This return(0) will never happen -- it's just to make the
                                      // compiler happy :-)
}

