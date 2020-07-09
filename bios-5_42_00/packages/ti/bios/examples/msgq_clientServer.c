/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== msgq_clientServer.c ========
 *  An example of message passing between TSKs.
 *
 */

#include <std.h>
#include <log.h>
#include <sem.h>
#include <sys.h>
#include <tsk.h>
#include <msgq.h>
#include <pool.h>
#include <staticpool.h>


/* The number of local message queues. */
#define NUMMSGQUEUES   4

/*
 *  Number of clients. Make sure there are enough message queues. 
 *  Note: this example only supports up to 10 client tasks.
 */
#define NUMCLIENTS     (NUMMSGQUEUES - 1)

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
    MSGQ_MsgHeader elem;    
    Uns            sequenceNumber;
} MyMsg;

/* The server's message queue handle */
static MSGQ_Queue serverMsgQueue;

/* Statically defined LOG object */
extern LOG_Obj trace;

/* The function prototypes. */
static Void serverThread(Void);
static Void clientThread(Arg arg);

/*
 *  ======== main ========
 *  Set-up the message queues and the clients and server TSKs.
 */
void main() 
{
    Int i;        
    MSGQ_Attrs  msgqAttrs;    
    SEM_Handle  serverSemHandle;
    Int         msgqStatus;
    TSK_Attrs   attrs;
    Char        *clientName[3];

    /* 
     *  Could have opened the client and server TSKs statically, but 
     *  having done dynamically for readability. Using default attributes
     */ 
    attrs = TSK_ATTRS;

    clientName[0] = "client0";
    clientName[1] = "client1";
    clientName[2] = "client2";

    for (i = 0; i < NUMCLIENTS; i++) {
        attrs.name = clientName[i];
        if (TSK_create((Fxn)clientThread, &attrs, (Arg)i) == NULL) {
            SYS_abort("Failed create client thread");
        }
    }
    
    /* Create the server TSK */
        attrs.name = "server";
    if (TSK_create((Fxn)serverThread, &attrs, NULL) == NULL) {
        SYS_abort("Failed create server thread");
    }

    /* 
     *  Could have created the semaphore statically, but 
     *  having done dynamically for readability.
     */        
    if ((serverSemHandle = SEM_create(0, NULL)) == NULL) {
        SYS_abort("Semaphore creation failed");
    }
    
    /* Open the server's message queue. */
    msgqAttrs              = MSGQ_ATTRS;
    msgqAttrs.notifyHandle = (Ptr)serverSemHandle;
    msgqAttrs.pend         = (MSGQ_Pend)SEM_pendBinary;
    msgqAttrs.post         = (MSGQ_Post)SEM_postBinary;
    
    msgqStatus = MSGQ_open("server", &serverMsgQueue, &msgqAttrs);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to open the server message queue");
    }        
}

/*
 *  ======== serverThread ========
 *  Receives message from all clients and processes it.  It then determines
 *  which client sent the message and returns it to them (with the seq number
 *  incremented).
 */
Void serverThread(Void)
{
    MyMsg *msg;
    Uint16 id;
    Int msgqStatus;    
    MSGQ_Queue replyQueue;

    for (;;) {
        msgqStatus = MSGQ_get(serverMsgQueue, (MSGQ_Msg *)&msg, SYS_FOREVER);
        if (msgqStatus != SYS_OK) {
            SYS_abort("Failed to get a message");
        }
        
        /* 
         *  Get the message id which corresponds to the id of the client in
         *  this application.
         */
        id = MSGQ_getMsgId((MSGQ_Msg)msg);
        LOG_printf(&trace, "Received msg from task %d with sequence #: %d", 
                   id, msg->sequenceNumber);

        /* Server will operate on the message...this case, just add one */
        msg->sequenceNumber++;

        /* Get the handle and send the message back. */
        msgqStatus = MSGQ_getSrcQueue((MSGQ_Msg)msg, &replyQueue);
        if (msgqStatus != SYS_OK) {
            /* Free the message and abort */
            MSGQ_free((MSGQ_Msg)msg);
            SYS_abort("Failed to extract handle from the message");            
        }
        
        /* Send the message back */
        msgqStatus = MSGQ_put(replyQueue, (MSGQ_Msg)msg);
        if (msgqStatus != SYS_OK) {
            /* Abort if there is an error */
            SYS_abort("Failed to send the message");        
        }
    }
}

/*
 *  ======== writerThread ========
 *  Sends a message, waits for the message back and then repeats. 
 *  The arg parameter contains the writer's id.
 *  Note: This TSK never ends, so we can use a local variable for
 *  the message queue name. Remember the message queue name must 
 *  be persistent.
 */
Void clientThread(Arg arg)
{
    MyMsg *msg;
    Uint16 id = ArgToInt(arg);
    Char   clientName[8];
    Int    msgqStatus;    
    MSGQ_Attrs msgqAttrs;
    MSGQ_Queue serverMsgQueue;
    MSGQ_Queue replyQueue;
    SEM_Handle replySemHandle;
    
    /* Locate the server's message queue handle */
    msgqStatus = MSGQ_locate("server", &serverMsgQueue, NULL);  
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to locate the message queue");        
    }
    
    /* 
     *  Could have created semaphore statically, but 
     *  having done dynamically for readability.
     */    
    if ((replySemHandle = SEM_create(0, NULL)) == NULL) {
        SYS_abort("Semaphore creation failed");
    }
        
    /* Open the client's message queue. */      
    msgqAttrs              = MSGQ_ATTRS;
    msgqAttrs.notifyHandle = (Ptr)replySemHandle;
    msgqAttrs.pend         = (MSGQ_Pend)SEM_pendBinary;
    msgqAttrs.post         = (MSGQ_Post)SEM_postBinary;
    
    /* Each message queue must have a unique name */
    clientName[0] = 'c';
    clientName[1] = 'l';
    clientName[2] = 'i';
    clientName[3] = 'e';
    clientName[4] = 'n';
    clientName[5] = 't';
    clientName[6] = (Char)id + '0';
    clientName[7] = '\0';
    
    msgqStatus = MSGQ_open(clientName, &replyQueue, &msgqAttrs);
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to open the message queue");        
    }
    
    /* Allocate a message */
    msgqStatus = MSGQ_alloc(STATICPOOLID, (MSGQ_Msg *)&msg, sizeof(MyMsg));
    if (msgqStatus != SYS_OK) {
        SYS_abort("Failed to allocate a message");        
    }

    /* Fill in the message */
    msg->sequenceNumber = 0;
    MSGQ_setMsgId((MSGQ_Msg)msg, id);
    MSGQ_setSrcQueue((MSGQ_Msg)msg, replyQueue);
    
    for (;;) {

        LOG_printf(&trace, "Task %d sending a msg with sequence #: %d", id, 
                   msg->sequenceNumber);        

        /* Send the message */
        msgqStatus = MSGQ_put(serverMsgQueue, (MSGQ_Msg)msg);
        if (msgqStatus != SYS_OK) {            
            SYS_abort("Failed to send the message");
        }

        /* Wait forever to get the message back */
        msgqStatus = MSGQ_get(replyQueue, (MSGQ_Msg *)&msg, SYS_FOREVER);
        if (msgqStatus != SYS_OK) {
            SYS_abort("Failed to get a message");
        }
        TSK_sleep(1); /* to simulate a delay */
    }
}
