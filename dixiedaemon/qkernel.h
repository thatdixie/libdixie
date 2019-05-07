// QKERNEL.H	 Definition file for Qkernel stuff.
//---------------------------------------------------------------------------
// History:
// --------
// 04/27/19 M. Gill    Refactored for libdixie implementation.
// 07/21/96 M. Gill    Initial pthread port.
// 07/11/96 M. Gill    Add includes for all CDaemon, and tcp classes.
// 01/10/95 M. Gill    Initial Solaris 2.5 port
// 01/10/85 M. Gill    Initial creation.
//---------------------------------------------------------------------------

#ifndef QKERNEL_H
#define QKERNEL_H

#include <DixieApp.h>
#include <pthread.h>
#include <qktypes.h>
#include <sem.h>
#include <queue.h> // watch this
#include <statetbl.h>
#include <asc.h>
#include <timer.h>
#include <fsm.h>
#include <resource.h>
#include <mos.h>
#include <sysevents.h>
#include <sigcatch.h>


//----------------
// Return codes
//----------------
#define SUCCESS    0
#define FAIL      -1

#endif








