// TEST.CPP 	DAEMON test startup module.
// ----------------------------------------------------------------------------
// History:
// --------
// 07/07/95 M. Gill       Initial creation.
// ----------------------------------------------------------------------------
#include <pthread.h>
#include <CDaemon.h>
#include <CDaemonEventLogger.h>
#include <CDaemonErrorLogger.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <qkernel.h>
#include <evl.h>
#include <ua_diag.h>
#include "test.h"

#define MAX_PROBABLE_THREADS	100

extern CDaemonEventLogger *event_log;
extern CDaemonErrorLogger *error_log;

//-----------------------------
// Here's all the global junk
//-----------------------------
TEST_DAEMON		*test_daemon;
TIMER			*mTimer;

static int Timeout( void *);

// ---------------------------------------------------------------------------
// FUNCTION: Timeout
//
// PURPOSE:	
//
// INPUT:	none
//
// RETURN:	none
// ---------------------------------------------------------------------------
static int Timeout(void *t)
{
    event_log->SendMessage("5 seconds!...");
    mTimer->Start(5, Timeout, 0);
    return(0);
}


// ---------------------------------------------------------------------------
// FUNCTION:    start()
//
// PURPOSE:     The function kicks off the application body of
//		the TEST Daemon. 
//
// INPUT:       None.
//
// RETURN:      Always 0.
// --------------------------------------------------------------------------- 
void TEST_DAEMON::start(int gc, char ** gv)
{
    int i,logging_level;

    logging_level =10;

    SetLoggingThreshold(logging_level);

    //-------------------------------------------
    // Register MAIN thread
    //-------------------------------------------
    event_log->Register(pthread_self(),"MAIN");
    error_log->Register(pthread_self(),"MAIN");
 
    event_log->SendMessage("Test event_log() 1 OK ...");
    event_log->SendMessage("Test event_log() 2 OK ...");

    mTimer = new TIMER;
    mTimer->Sleep(1);

    error_log->SendMessage(1,"Test error_log() 1 OK ...");
    error_log->SendMessage(1,"Test error_log() 2 OK ...");

    mTimer->Start(5,Timeout, (void *)0);

    //---------------------------------------------------------
    // Setup TCP/IP server and associate with User Agents...
    //---------------------------------------------------------
    TCP_SERVER *tcps       = new TCP_SERVER(9001, 10);
    UA_DIAG    *diag_ports = new UA_DIAG[10];
    
    for(i=0; i<10;i++,diag_ports++)
    {
	diag_ports->start(tcps, i);
    }

    //-----------------------------------------
    // Load conf file from where we are and
    // event_log values for "foo" and "bar"...
    //-----------------------------------------
    config->open("./testd.conf", this);
    config->load();

    event_log->SendMessage(config->get("foo").c_str());
    event_log->SendMessage(config->get("bar").c_str());
    
    return;    

}


//-------------------------------------------------------------
TEST_DAEMON::TEST_DAEMON(const char *appcode, const char *logdir) 
			: CDaemon(appcode, logdir)
{
    return;
}


//---------------------------------------
// test_daemon main
//---------------------------------------
int main(int argc, char **argv)
{
    test_daemon = new TEST_DAEMON("testd", argv[1]);
 
    test_daemon->RunForeground(argc, argv, MAX_PROBABLE_THREADS);
  
    return(0);
}
