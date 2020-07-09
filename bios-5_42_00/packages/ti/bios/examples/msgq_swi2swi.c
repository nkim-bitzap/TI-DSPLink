/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== msgq_swi2swi.c ========
 *  An example of an asynchronous locate and message passing between SWIs.
 *
 */

#include <std.h>
#include <log.h>
#include <swi.h>
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

/* Message queue handles for the worker and boss SWIs */
MSGQ_Queue workerMsgQueue;
MSGQ_Queue bossMsgQueue;

/* Statically defined LOG object */
extern LOG_Obj trace;

/* The function prototypes. */
Void workerThread(Void);
Void bossThread(Void);

/*
 *  ======== main ========
 *  Set-up the message queues and the worker and boss tasks.
 */
void main() 
{
    SWI_Attrs   swiAttrs;
    SWI_Handle  workerSwiHandle;
    SWI_Handle  bossSwiHandle;
    MSGQ_Attrs  msgqAttrs;
    Int         msgqStatus;    
   
    /* 
     *  Could have created the SWI's statically, but 
     *  having done dynamically for readability.
     */

    swiAttrs = SWI_ATTRS;
    swiAttrs.fxn = (SWI_Fxn)bossThread;    
    if ((bossSwiHandle = SWI_create(&swiAttrs)) == NULL) {
        SYS_abort("Failed to create boss thread");
    }

    /* 
     *  Change only the function field.  The others are the 
     *  same as the previous SWI.
     */
    swiAttrs.fxn = (SWI_Fxn)workerThread;    
    if ((workerSwiHandle = SWI_create(&swiAttrs)) == NULL) {
        SYS_abort("Failed to create worker thread");
    }
    
    /* 
     *  Open the worker's message queue. 
     *  Since the worker is a SWI, use the default 
     *  pend function (which is a basically a nop).
     */      
    msgqAttrs              = MSGQ_ATTRS;
    msgqAttrs.notifyHandle = (Ptr)workerSwiHandle;
    msgqAttrs.post         = (MSGQ_Post)SWI_post;
    
    msgqStatus = MSGQ_open("worker", &workerMsgQueue, &msgqAttrs);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to open the message queue");
    }

    /* 
     *  Open the boss's message queue. This is to receive the 
     *  asynchronous locate message.
     *  Since the boss is a SWI, there is no pend function.     
     * 
     *  Change only the notifyHandle field.  The others are the 
     *  same as the previous message queue.
     */      
    msgqAttrs.notifyHandle = (Ptr)bossSwiHandle;
    
    msgqStatus = MSGQ_open("boss", &bossMsgQueue, &msgqAttrs);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to open the message queue");
    }
    
    /* Start the boss SWI */
    SWI_post(bossSwiHandle);
}

/*
 *  ======== workerThread ========
 *  Receives message, processes it and frees it. 
 */
Void workerThread(Void)
{
    MyMsg *msg;
    Int msgqStatus;
    MSGQ_Queue replyQueue;
    
    /* 
     *  Since the worker is a SWI and it is running, there should be a 
     *  message waiting for it. 
     *  Generally in a SWI, you would process all the messages present 
     *  in a message queue.  In this example there will only be one.
     */    
    for (;;) {

        msgqStatus = MSGQ_get(workerMsgQueue, (MSGQ_Msg *)&msg, 0);
        if (msgqStatus != SYS_OK) {
            /* No messages to process */
            return;
        }

        /* Make sure the message is the one the SWI is expecting */
        if (MSGQ_getMsgId((MSGQ_Msg)msg) != MESSAGEID) {
            SYS_abort("Unexpected message"); 
        }        

        LOG_printf(&trace, "Received msg with seq #: %d", msg->sequenceNumber);
        msg->sequenceNumber++;

        /* Get the handle and send the message back. */
        msgqStatus = MSGQ_getSrcQueue((MSGQ_Msg)msg, &replyQueue);
        if (msgqStatus != SYS_OK) {            
            SYS_abort("Failed to extract handle from the message");            
        }
        
        msgqStatus = MSGQ_put(replyQueue, (MSGQ_Msg)msg);
        if (msgqStatus != SYS_OK) {            
            SYS_abort("Failed to send the message");        
        }
    }
}

/*
 *  ======== bossThread ========
 *  Receives the asynchronous locate message, sends a message
 *  and then terminates.
 */
Void bossThread(Void)
{
    MyMsg *msg;
    Int    msgqStatus;
    static Bool firstTime = TRUE;
    static MSGQ_Queue workerMsgQueue = MSGQ_INVALIDMSGQ;
    MSGQ_LocateAsyncAttrs locateAsyncAttrs;

    if (firstTime == TRUE) {
        /* Start the asynchronous locate */
        locateAsyncAttrs        = MSGQ_LOCATEASYNCATTRS;
        locateAsyncAttrs.poolId = STATICPOOLID;
        msgqStatus = MSGQ_locateAsync("worker", bossMsgQueue, &locateAsyncAttrs);
        if (msgqStatus != SYS_OK) {
            SYS_abort("Failed to start the async. locate");
        }
        firstTime = FALSE;
        return;
    }
    
    /* Get the message. */
    msgqStatus = MSGQ_get(bossMsgQueue, (MSGQ_Msg *)&msg, 0);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to get a message");
    }

    /*
     *  Before this SWI can send any messages, the worker message queue must
     *  be located.  The async. locate was started in at the beginning of this
     *  SWI.
     *  Check here to see if this message is an async locate message.  If it is:
     *      1. get the located msgqQueue from the message
     *      2. free the message
     *      3. allocate and initialize a new message.
     *  The only other type of message this SWI receives is a message from
     *  the worker SWI.
     */
    if (MSGQ_getMsgId((MSGQ_Msg)msg) == MSGQ_ASYNCLOCATEMSGID) {
        /* 
         *  Extract the located message queue handle from the message 
         *  and then free the asynchronous locate message.
         */
        workerMsgQueue = ((MSGQ_AsyncLocateMsg *)msg)->msgqQueue;
        MSGQ_free((MSGQ_Msg)msg);        
 
        /* Allocate a message to send to the worker. */
        msgqStatus = MSGQ_alloc(STATICPOOLID, (MSGQ_Msg *)&msg, sizeof(MyMsg));
        if (msgqStatus != SYS_OK) {
            SYS_abort("Failed to allocate a message");            
        }
         
        /* Fill in the message */
        msg->sequenceNumber = 0;
        MSGQ_setMsgId((MSGQ_Msg)msg, MESSAGEID);
        MSGQ_setSrcQueue((MSGQ_Msg)msg, bossMsgQueue);
    }

    /*
     *  Make sure the worker message queue has been located before 
     *  sending a message.
     */
    if (workerMsgQueue != MSGQ_INVALIDMSGQ) {

        LOG_printf(&trace, "Sending a msg with seq #: %d", 
                   msg->sequenceNumber);

        /* Send the message.  If the send fails, abort */
        msgqStatus = MSGQ_put(workerMsgQueue, (MSGQ_Msg)msg);
        if (msgqStatus != SYS_OK) {
            SYS_abort("Failed to send the message");           
        }
    }    
}
