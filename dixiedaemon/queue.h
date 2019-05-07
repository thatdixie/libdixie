// QUEUE.H	 Definition file for QUEUE class.
//-----------------------------------------------------------------------------
// History:
// --------
// 12/29/95 M. Gill	Initial creation.
//----------------------------------------------------------------------------
#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H

#include <qktypes.h>

typedef struct
{
    LPNODE head;
    LPNODE tail;

}QUEUE_STRUCT;

class FIFO_QUEUE
{

protected:

    QUEUE_STRUCT queue;

public:

    FIFO_QUEUE(void);
    ~FIFO_QUEUE(void);
    int Enqueue(LPNODE);
    LPNODE Dequeue(void);
};
#endif
