/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/**********************************************************************

        For Dbus base library Implementation,
        Common Component Software Platform (CCSP)

    ---------------------------------------------------------------

    environment:

        platform dependent

    ---------------------------------------------------------------

    author:

        Qiang Tu

    ---------------------------------------------------------------

    revision:

        06/17/11    initial revision.

**********************************************************************/

#ifndef CCSP_MESSAGE_BUS_H
#define CCSP_MESSAGE_BUS_H

#include <pthread.h>

/* temp solution to fix rbus build issues after removing dbus.h */
typedef enum
{
    DBUS_HANDLER_RESULT_HANDLED,
    DBUS_HANDLER_RESULT_NOT_YET_HANDLED,
    DBUS_HANDLER_RESULT_NEED_MEMORY
}DBusHandlerResult;

/*
notes: see readme.txt
*/

//match the error code in ccsp_base_api.h
#define CCSP_Message_Bus_OK             100
#define CCSP_Message_Bus_OOM            101
#define CCSP_Message_Bus_ERROR          102

#define CCSP_MESSAGE_BUS_CANNOT_CONNECT 190
#define CCSP_MESSAGE_BUS_TIMEOUT        191
#define CCSP_MESSAGE_BUS_NOT_EXIST      192
#define CCSP_MESSAGE_BUS_NOT_SUPPORT    193 //remote can't support this api

#define WRITEID         "WRITEID"
#define PARAM_SIZE      "PARAM_SIZE"
#define SESSIONID       "SESSIONID"
#ifdef COMMIT
    #undef COMMIT
#endif
#define COMMIT          "COMMIT"
#define INVALID_PARAM   "INVALID_PARAM"
#define RESULT          "RESULT"
#define OBJNAME         "OBJNAME"
#define INST_NUM        "INST_NUM"
#define PRIORITY        "PRIORITY"
#define PARAM_NAME      "PARAM_NAME"
#define NEXT_LEVEL      "NEXT_LEVEL"


typedef void*(*CCSP_MESSAGE_BUS_MALLOC) ( size_t size ); // this signature is different from standard malloc
typedef void (*CCSP_MESSAGE_BUS_FREE)   ( void * ptr );

typedef struct _CCSP_MESSAGE_BUS_INFO
{
    char      component_id[256];
    void * CcspBaseIf_func;
    CCSP_MESSAGE_BUS_MALLOC  mallocfunc ;
    CCSP_MESSAGE_BUS_FREE      freefunc ;
    void* rbus_callback;

} CCSP_MESSAGE_BUS_INFO;

typedef struct _CCSP_DEADLOCK_DETECTION_INFO
{
    pthread_mutex_t info_mutex;
    char *          messageType;
    void *          parameterInfo;
    unsigned long   size;
    unsigned long   enterTime;
    unsigned long   detectionDuration;
    unsigned long   timepassed;

} CCSP_DEADLOCK_DETECTION_INFO;

#define deadlock_detection_log_linenum 200
#define deadlock_detection_log_linelen 192 
#define deadlock_detection_log_file    "/var/log/ccsp_emergency.log"

typedef char DEADLOCK_ARRAY[deadlock_detection_log_linenum][deadlock_detection_log_linelen];

// void ccsp_msg_check_resp_sync (DBusPendingCall *pcall, void *user_data); // local, RTian 07/03/2013

// EXTERNAL INTERFACES

void CCSP_Msg_SleepInMilliSeconds(int milliSecond);

/*if mallocfunc, freefunc,config_file is NULL, default value will be used */
int CCSP_Message_Bus_Init
(
    char*             component_id,
    char * config_file,
    void **bus_handle,
    CCSP_MESSAGE_BUS_MALLOC mallocfunc,
    CCSP_MESSAGE_BUS_FREE   freefunc
);

void CCSP_Message_Bus_Exit
(
    void *bus_handle
);

#endif

