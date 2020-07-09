/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== msgq_tsk2tsk.c ========
 *  An example of an synchronous locate and message passing between tasks.
 *
 */

#include <std.h>
#include <log.h>
#include <sem.h>
#include <tsk.h>
#include <sys.h>
#include <msgq.h>
#include <pool.h>
#include <staticpool.h>

/* Id of the message */
#define MESSAGEID      1

/* The number of local message queues. */
#define NUMMSGQUEUES   4

/* 
 *  Size of the messages in the allocator 
 *  This must be a multiple of 8 MADUs as required by the
 *  static allocator.
 */
#define MSGSIZE       64  

/* Number of messages in the allocators */
#define NUMMSGS       NUMMSGQUEUES * 4

/* One processor in this system */
#define NUMPROCESSORS 1

/* The allocator id and the number of allocators. */
enum {
    STATICPOOLID = 0,
    NUMALLOCATORS
};

/* 
 *  Allocator Static Configuration 
 *  The STATICPOOL allocator will internally force an 8 MADUs
 *  alignment on the buffer.  Use DATA_ALIGN to eliminate memory waste.
 */
#if defined(_28L_)
/* 
 *  #pragma DATA_ALIGN currently not supported in the 28x codegen tools. 
 *  Adding 8 to insure that there is enough memory in case the allocator
 *  needs to round to an 8 MADUs boundary.
 */
Char staticBuf[MSGSIZE * NUMMSGS + 8];
#else
#pragma DATA_ALIGN(staticBuf, 8)
Char staticBuf[MSGSIZE * NUMMSGS];
#endif

static STATICPOOL_Params staticPoolParams = 
        {staticBuf,                        /* Buffer to partition.   */
         sizeof(staticBuf),                /* Size of the buffer     */
         MSGSIZE};                         /* Message size           */

static STATICPOOL_Obj staticPoolObj;

static POOL_Obj allocators[NUMALLOCATORS] = 
    {{STATICPOOL_init,                     /* Allocator init function       */
      (POOL_Fxns *)&STATICPOOL_FXNS,       /* Allocator interface functions */
      &staticPoolParams,                   /* Allocator configuration       */
      &staticPoolObj}};                    /* Allocator object              */

POOL_Config  POOL_config = {allocators, NUMALLOCATORS};

/* 
 *   MSGQ Configuration  
 */
static MSGQ_Obj msgQueues[NUMMSGQUEUES];

static MSGQ_TransportObj transports[NUMPROCESSORS] = {MSGQ_NOTRANSPORT};

MSGQ_Config MSGQ_config = {msgQueues,         /* Array of message queues     */
                           transports,        /* Array of transports         */
                           NUMMSGQUEUES,      /* # of message queues in array*/
                           NUMPROCESSORS,     /* # of transports in array    */
                           0,                 /* 1st uninitialized msg queue */
                           MSGQ_INVALIDMSGQ,  /* no error handler queue      */
                           POOL_INVALIDID};   /* allocator id for errors     */

/* The format of the messages being sent. */
typedef struct MyMsg {
    MSGQ_MsgHeader header;
    Uns            sequenceNumber;
} MyMsg;

/* Statically defined LOG object */
extern LOG_Obj trace;

MSGQ_Queue workerMsgQueue;
MSGQ_Queue bossMsgQueue;

/* The function prototypes. */
Void workerThread(Void);
Void bossThread(Void);

/*
 *  ======== main ========
 *  Set-up the message queues and the worker and boss tasks.
 */
void main() 
{
    Int        msgqStatus;
    MSGQ_Attrs msgqAttrs;
    SEM_Handle workerSemHandle;
    SEM_Handle bossSemHandle;
    TSK_Attrs  attrs = TSK_ATTRS;

    /* 
     *  Could have created the semaphores statically, but 
     *  having done dynamically for readability.
     */
   
    workerSemHandle = SEM_create(0, NULL);
    bossSemHandle = SEM_create(0, NULL);
    if ((workerSemHandle == NULL) || (bossSemHandle == NULL)) {
        SYS_abort("Semaphore creation failed");
    }

    /*
     *  Open the worker message queue.  
     *  Using semaphores as the notification mechanism.
     */
    msgqAttrs              = MSGQ_ATTRS;
    msgqAttrs.notifyHandle = (Ptr)workerSemHandle;
    msgqAttrs.pend         = (MSGQ_Pend)SEM_pendBinary;
    msgqAttrs.post         = (MSGQ_Post)SEM_postBinary;
    msgqStatus = MSGQ_open("worker", &workerMsgQueue, &msgqAttrs);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to open the worker message queue");
    }

    /* 
     *  Open the boss message queue. 
     *  Use the same settings for the attributes except a different SEM handle.
     */
    msgqAttrs.notifyHandle = (Ptr)bossSemHandle;
    msgqStatus = MSGQ_open("boss", &bossMsgQueue, &msgqAttrs);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to open the boss message queue");
    }

    /*
     *  Create the boss and worker threads. Taking the default TSK attributes. 
     */
 
    attrs.name = "boss";
    if (TSK_create((Fxn)bossThread, &attrs) == NULL) {
            SYS_abort("Failed create boss thread");
    }

    attrs.name = "worker";
    if (TSK_create((Fxn)workerThread, &attrs) == NULL) {
        SYS_abort("Failed create worker thread");
    }
}

/*
 *  ======== workerThread ========
 *  Receives message, processes it and returns it back. 
 */
Void workerThread(Void)
{    
    MyMsg     *msg;
    Int        msgqStatus;
    MSGQ_Queue replyMsgQueue;

    /*
     *  Locate the boss's message queue handle.
     *  Passing NULL for the attributes, so it is a
     *  synchronous locate.
     */
    msgqStatus = MSGQ_locate("boss", &replyMsgQueue, NULL);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to locate the reply message queue");
    }

    /* While there is no problem, keep processing messages. */
    for (;;) {

        /* Wait forever to get a message */
        msgqStatus = MSGQ_get(workerMsgQueue, (MSGQ_Msg *)&msg, SYS_FOREVER);
        if (msgqStatus != SYS_OK) {
            SYS_abort("Failed to get a message");
        }

        LOG_printf(&trace, "Received msg with seq #: %d", msg->sequenceNumber);

        /* Send the message back. */
        msgqStatus = MSGQ_put(replyMsgQueue, (MSGQ_Msg)msg);
        if (msgqStatus != SYS_OK) {
            /* Need to free the message */
            MSGQ_free((MSGQ_Msg)msg);
            SYS_abort("Failed to send the message");
        }
    }
}

/*
 *  ======== bossThread ========
 *  Sends a message, waits for the message back and then repeat. 
 */
Void bossThread(Void)
{
    MyMsg     *msg;
    Int        msgqStatus;
    MSGQ_Queue dstMsgQueue;

    /*
     *  Locate the worker's message queue handle.
     *  Passing NULL for the attributes, so it is a
     *  synchronous locate.
     */
    msgqStatus = MSGQ_locate("worker", &dstMsgQueue, NULL);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to locate the worker message queue");
    }

    /* Allocate a message */
    msgqStatus = MSGQ_alloc(STATICPOOLID, (MSGQ_Msg *)&msg, sizeof(MyMsg));
    if (msgqStatus != SYS_OK) {        
        SYS_abort("Failed to allocate a message");
    }

    /* Initialize the sequence number */
    msg->sequenceNumber = 0;

    for (;;) {

        LOG_printf(&trace, "Sending a msg with seq #: %d", 
                   msg->sequenceNumber);

        /* Send the message */
        msgqStatus = MSGQ_put(dstMsgQueue, (MSGQ_Msg)msg);
        if (msgqStatus != SYS_OK) {
            SYS_abort("Failed to send a message");
        }        
        
        /* Wait forever for the reply */
        msgqStatus = MSGQ_get(bossMsgQueue, (MSGQ_Msg *)&msg, SYS_FOREVER);
        if (msgqStatus != SYS_OK) {
            SYS_abort("Failed to get a message");
        }        

        msg->sequenceNumber++;
        TSK_sleep(1); /* to simulate a delay */
    }
}
