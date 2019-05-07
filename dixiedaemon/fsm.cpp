// FSM.CPP	Finite State Machine Application Class.
//----------------------------------------------------------------------------
// History:
// --------
// 04/27/19 M. Gill     Refactored for libdixie implementation.
// 07/14/96 M. Gill	New single instance FSM.
// 01/10/96 M. Gill	Initial Solaris port.
// 04/26/95 M. Gill	Initial C++ (QCYCLE) port.
// 01/10/85 M. Gill	Initial creation.
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fsm.h>

extern MOS *event_log;

//----------------------------------------------------------------------------
// FUNCTION FSM::Main
//
// PURPOSE:	This is the execution body of the FSM task.
//		The FSM (Finite State Machine) task is started at 
//		initialization and never terminates.
//
// INPUT:	p = Pointer to application context (port) 
//		    attached to this task.
//
// PROCESS:	1) Wait for received message via FSM::RcvMsg()
//		2) Translate message to event/data.
//		3) Execute function associated with translated event.
//----------------------------------------------------------------------------
int FSM::fsmMain(FSM *o)
{
    STATE_TABLE_ENTRY *transition;
    FSM_PORT *p =o->appPort;
    FSM_MSG   *n;
    int current_state, event, data;
    void *d_ptr;

    for( ;; )
    {
	n = o->fsmRcvMsg();		  // Get a Message Node
	event = n->event;		  // Save the Event
	data  = n->data;		  // Save the Data
	d_ptr = n->d_ptr;		  // ... & Data Pointer
	o->fsmRelMsg(n);       	          // Release message node
	current_state = p->current_state; // Save Current State
	p->event = event;
	transition = &p->State[current_state][event];
	p->current_state = transition->next_state;    // Set the Next State
	p->current_state_save = current_state;
	((p->mThisPointer) ->* (transition->action))(data, d_ptr);
    }

    return 0; // Never reached
}


//----------------------------------------------------------------------------
// FUNCTION FSM::fsmRcvMsg
//
// PURPOSE:	Retrieve message node from queue.
// INPUT:	Pointer to FSM_PORT.
// RETURN:	Pointer to message node.
//
// PROCESS:	1) Use SEM::wait(), to wait for message signal.
//		2) FSM::send() will use SEM::signal() to wake up this task.
//----------------------------------------------------------------------------
FSM_MSG *FSM::fsmRcvMsg()
{
    msg_sem->wait();

    return((FSM_MSG *)msgque->dequeue());
}


//----------------------------------------------------------------------------
// FUNCTION FSM::send
//
// PURPOSE:	Place message node into queue.
//
// INPUT:
// 		1) event.
//		2) event data.
//		3) optional data pointer.
//
// PROCESS:	1) Allocate Message node.
//		2) Place message on FSM message queue.
//		3) signal FSM task.
//
// RETURN:	FAIL    => Can't allocate message node.
//		SUCCESS => OK
//----------------------------------------------------------------------------
int FSM::send(int event, int data, void *d_ptr)
{
    FSM_PORT *p = appPort;
    FSM_MSG  *msg;

    // -------------------------
    //  Allocate a message node
    // -------------------------
    msg = new FSM_MSG();
    
    msg->event = event;
    msg->data  = data;
    msg->d_ptr = d_ptr;

    msgque->enqueue(msg); // Send messgae
    msg_sem->signal();	  // wake up pending task
    return( SUCCESS );
}




//----------------------------------------------------------------------------
// FUNCTION FSM::RelMsg
//
// PURPOSE:	Release message node .
//
// INPUT:	1) pointer to FSM_PORT
//		2) Pointer to message node.
//----------------------------------------------------------------------------
void FSM::fsmRelMsg(FSM_MSG *n)
{
    delete n;
}


//---------------------------------------------------------------------------
// FUNCTION FSM::invalidEvent()
//
// PURPOSE: This method is called on an unexpected Event/Transition
//---------------------------------------------------------------------------
int FSM::invalidEvent(int arg1, void *n)
{
    char message_buffer[80];
    FSM_PORT *port =appPort;

    sprintf(message_buffer,"Event #%d while in state %d", 
	    port->event, port->current_state_save);

    event_log->SendMessage(message_buffer);

    return(0);
}


//---------------------------------------------------------------------------
// Function: DoNothing()
// 
// Purpose:     Do Nothing.
//
// INPUTS:      Action routine.
// RETURN:      N/A
//---------------------------------------------------------------------------
int FSM::doNothing(int arg1, void *n)
{
    return(0);
}


//----------------------------------------------------------------------------
// FUNCTION FSM::Attach()
//
// PURPOSE:	Attach state table to FSM task.
//
// INPUT:	1) pointer to STATE_TABLE
//		2) Pointer to application context.
//----------------------------------------------------------------------------
void FSM::attach(STATE_TABLE *app_table)
{
    int i,j;
    STATE_TABLE        *st;
    STATE_TABLE_ENTRY  *ste;
    FSM_PORT           *port = appPort;

    //--------------------------------
    // Initialize default entry.
    //--------------------------------
    for( i = 0; i < NUMBER_OF_STATES; i++ )
    {
	for( j = 0; j < NUMBER_OF_EVENTS; j++ )
	{
	    port->State[i][j].action = (ACTION_FUNC) &FSM::invalidEvent;
	    port->State[i][j].next_state = i;
	}
    }
    //-------------------------
    // Initialize application 
    // state table.
    //-------------------------- 
    for(st = app_table; st->current_state != NUMBER_OF_STATES; st++)
    {
	ste = &port->State[st->current_state][st->transition];
	ste->next_state = st->next_state;
	ste->action = st->action;
    }
    //------------------------
    // Set initial conditions.
    //------------------------
    port->current_state =0;
    port->next_state = 0;
    return;
}


//----------------------------------------------------------------------------
// FUNCTION FSM::start()
//
// PURPOSE: Kickoff application.
//
// INPUT:	1) Pointer to Application State Table.
//		2) Channel Number.
//
// RETURN:	NONE
//----------------------------------------------------------------------------
void FSM::start(STATE_TABLE *app_table, int channel_num)
{
    int i,j,rc;
    FSM_PORT *port;

    appPort = new FSM_PORT;	// Allocate FSM_PORT 

    port=appPort;
    attach(app_table);		// Attach application state table
    port->channel = channel_num;// Assign channel number.
    port->timer   = new TIMER;	// Create local timer.
    port->mThisPointer = this;

    msgque  = new Queue<FSM_MSG *>; // Create the message queue
    msg_sem = new SEM(0);	    // Create message semaphore.
    
    //----------------------------------
    // Create thread for execution body
    //----------------------------------
    port->thread_stack_size = FSM_STACK_SIZE;
    pthread_attr_init(&port->thread_attr);
    /*pthread_attr_setstacksize(
			      &port->thread_attr,
			      port->thread_stack_size); */
    rc =pthread_create(&port->thread_id,            // Thread ID 
		       &port->thread_attr,          // Thread attributes
                       (void * (*)(void *))fsmMain, // Start function
                       (void *)this );              // Start function Argument

    send(INIT_OK,0,0);		     // Send initial event

    return;
}


//----------------------------------------------------------------------------
// FUNCTION FSM::~FSM()
//
// PURPOSE: Destructor.
//
// INPUT:	NONE
//
// RETURN:	NONE
//----------------------------------------------------------------------------
FSM::~FSM(void)
{
    return;
}


//----------------------------------------------------------------------------
// FUNCTION FSM::FSM(void)
//
// PURPOSE:     Constructor.
//
// INPUT:	NONE.
//
// RETURN:	NONE.
//----------------------------------------------------------------------------
FSM::FSM(void)
{

}
FSM_MSG::FSM_MSG(void)
{

}
FSM_MSG::~FSM_MSG(void)
{

}
