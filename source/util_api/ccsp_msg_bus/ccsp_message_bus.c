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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <ccsp_message_bus.h>
#include "ccsp_base_api.h"
#include "ccsp_trace.h"
#include <fcntl.h>
#include <rbus_message_bus.h>
#include "ansc_platform.h"
#include <dslh_definitions_database.h>
#include "ccsp_rbus_value_change.h"
#include "ccsp_rbus_intervalsubscription.h"
#include "safec_lib_common.h"

#include <sys/time.h>
#include <time.h>

#ifdef _DEBUG
// #define _DEBUG_LOCAL_
#endif

extern void rbusFilter_InitFromMessage(rbusFilter_t* filter, rbusMessage msg);
extern void rbusEventData_appendToMessage(rbusEvent_t* event, rbusFilter_t filter, uint32_t interval, uint32_t duration, int32_t componentId, rbusMessage msg);

static int               CCSP_Message_Bus_Register_Path_Priv_rbus(void*, rbus_callback_t, void*);
static int               thread_path_message_func_rbus(const char * destination, const char * method, rbusMessage in, void * user_data, rbusMessage *out, const rtMessageHeader* hdr);
static int tunnelStatus_signal_rbus(const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr);
static int webcfg_signal_rbus (const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr);
static int wifiDbStatus_signal_rbus(const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr);
static int telemetry_send_signal_rbus(const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr);
static int cssp_event_subscribe_override_handler_rbus(char const* object,  char const* paramName,  char const* eventName, char const* listener, int added, int componentId, int interval, int duration, rbusFilter_t filter, void* userData);
static void Ccsp_Rbus_ReadPayload(rbusMessage payload, int32_t* componentId, int32_t* interval, int32_t* duration, rbusFilter_t* filter);

void 
CCSP_Msg_SleepInMilliSeconds
(
    int milliSecond
)
{
    struct timeval tm;
    tm.tv_sec = milliSecond/1000;
    tm.tv_usec = (milliSecond%1000)*1000;
    select(0, NULL, NULL, NULL, &tm);
}

void
ccsp_rbus_logHandler
(
    rbusLogLevel level,
    const char* file,
    int line,
    int threadId,
    char* message
)
{
    UNREFERENCED_PARAMETER(threadId);
    switch (level)
    {
        case RBUS_LOG_FATAL:
            CcspTraceCritical(("%s:%d %s\n", file, line, message));
            break;
        case RBUS_LOG_ERROR:
            CcspTraceError(("%s:%d %s\n", file, line, message));
            break;
        case RBUS_LOG_WARN:
            CcspTraceWarning(("%s:%d %s\n", file, line, message));
            break;
        case RBUS_LOG_INFO:
            CcspTraceInfo(("%s:%d %s\n", file, line, message));
            break;
        case RBUS_LOG_DEBUG:
            CcspTraceDebug(("%s:%d %s\n", file, line, message));
            break;
    }
    return;
}

int 
CCSP_Message_Bus_Init
(
    char *component_id,
    char *config_file,
    void **bus_handle,
    CCSP_MESSAGE_BUS_MALLOC mallocfc,
    CCSP_MESSAGE_BUS_FREE   freefc

)
{
    FILE                  *fp              = NULL;
    CCSP_MESSAGE_BUS_INFO *bus_info        = NULL;

    static void *stashedHandleForTelemetry = NULL; /*added for telemetry*/

    /*if its telemetry and we have a stashed handle, give it back
      if no handle yet (which is unexpected) then do full init so t2 gets something back
    */
    /*CID: 144417 Dereference before null check*/
    if(component_id && strcmp(component_id, "com.cisco.spvtg.ccsp.t2commonlib") == 0)
    {
        if(stashedHandleForTelemetry)
        {
            CcspTraceWarning(("<%s>: telemetry2_0 stashed handle returned\n", __FUNCTION__));
            *bus_handle = stashedHandleForTelemetry;
            return 0;
        }
        else
        {
            CcspTraceWarning(("<%s>: telemetry2_0 stashed handle does not exist so creating new\n", __FUNCTION__));
        }
    }

    if(!config_file)
        config_file = "ccsp_msg.cfg";

    if ((fp = fopen(config_file, "r")) == NULL) {
        CcspTraceError(("<%s>: cannot open %s, try again after a while\n", __FUNCTION__, config_file));
        sleep(2);

        if ((fp = fopen(config_file, "r")) == NULL) {
            CcspTraceError(("<%s>: cannot open %s\n", __FUNCTION__, config_file));
            return -1;
        }
    }
        
    // alloc memory, assign return value
    if(mallocfc) bus_info =(CCSP_MESSAGE_BUS_INFO*) mallocfc(sizeof(CCSP_MESSAGE_BUS_INFO));
    else bus_info =(CCSP_MESSAGE_BUS_INFO*) malloc(sizeof(CCSP_MESSAGE_BUS_INFO));
    if( ! bus_info)
    {
        CcspTraceError(("<%s>: No memory\n", __FUNCTION__));
        fclose(fp);/*RDKB-6234, CID-33427, free the resource before return*/
        return -1;
    }
    memset(bus_info, 0, sizeof(CCSP_MESSAGE_BUS_INFO));
    *bus_handle = bus_info; // return

    /*stash this for telemetry*/
    stashedHandleForTelemetry = *bus_handle;

    // assign malloc and free func
    if(mallocfc) bus_info->mallocfunc = mallocfc;
    else bus_info->mallocfunc = malloc;
    if(freefc) bus_info->freefunc = freefc ;
    else bus_info->freefunc = free ;

    // bus name
    if(component_id) {
       strncpy(bus_info->component_id, component_id , sizeof(bus_info->component_id) -1);
       bus_info->component_id[sizeof(bus_info->component_id)-1] = '\0';
    }

        rbusCoreError_t err = RBUSCORE_SUCCESS;
        CCSP_Message_Bus_Register_Path_Priv_rbus(bus_info, thread_path_message_func_rbus, bus_info);

        /* Register with rbusLog to use CCSPTRACE_LOGS */
        rbus_registerLogHandler(ccsp_rbus_logHandler);
        int rc;
        rbusHandle_t handle;
        rc = rbus_open(&handle, component_id);
        if(rc != RBUS_ERROR_SUCCESS)
        {
            CcspTraceError(("%s(%s): rbus_open failed: %d\n",  __FUNCTION__, component_id, rc));
            fclose(fp);
            bus_info->freefunc(bus_info);
            *bus_handle = NULL;
            return -1;
        }
        else
        {
            CcspTraceInfo(("connection opened for %s\n",component_id));

            if((rc = rbus_unregisterObj(component_id)) != RBUSCORE_SUCCESS)
            {
                CcspTraceError(("%s(%s): rbus_unregisterObj error %d\n", __FUNCTION__, component_id, rc));
                rbus_close(handle);
                fclose(fp);
                bus_info->freefunc(bus_info);
                *bus_handle = NULL;
                return -1;
            }
            else
            {
                bus_info->rbus_handle = handle;
                if((err = rbus_registerObj(component_id, (rbus_callback_t) bus_info->rbus_callback, bus_info)) != RBUSCORE_SUCCESS)
                {
                    CcspTraceError(("<%s>: rbus_registerObj fails for %s\n", __FUNCTION__, component_id));
                }
                else
                {
                    if(strcmp(component_id,"eRT.com.cisco.spvtg.ccsp.tr069pa") == 0)
                    {
                        if((err = rbus_registerEvent(component_id,CCSP_DIAG_COMPLETE_SIGNAL,NULL,NULL)) != RBUSCORE_SUCCESS)
                            RBUS_LOG_ERR("%s : rbus_registerEvent returns Err: %d for diagCompleteSignal\n", __FUNCTION__, err);
                    }
                    else if(strcmp(component_id,"eRT.com.cisco.spvtg.ccsp.rm") == 0)
                    {
                        if((err = rbus_registerEvent(component_id,CCSP_SYSTEM_REBOOT_SIGNAL,NULL,NULL)) != RBUSCORE_SUCCESS)
                            RBUS_LOG_ERR("%s : rbus_registerEvent returns Err: %d for systemRebootSignal", __FUNCTION__, err);
                    }
                    else if(strcmp(component_id,"eRT.com.cisco.spvtg.ccsp.webpaagent") == 0)
                    {
                        rbus_method_table_entry_t table[1] = {
                            {"webconfigSignal", (void*)bus_info, webcfg_signal_rbus},
                        };
                        if(( err = rbus_registerMethodTable(component_id, table, 1) != RBUSCORE_SUCCESS ))
                        {
                            RBUS_LOG_ERR("%s : rbus_registerMethodTable returns Err: %d",  __FUNCTION__, err);
                        }
                    }
                    else if(strcmp(component_id,"eRT.com.cisco.spvtg.ccsp.wifi") == 0)
                    {
                        rbus_method_table_entry_t table[2] = {
                            {"TunnelStatus", (void*)bus_info, tunnelStatus_signal_rbus},
                            {"WifiDbStatus", (void*)bus_info, wifiDbStatus_signal_rbus},
                        };
                        if(( err = rbus_registerMethodTable(component_id, table, 2) != RBUSCORE_SUCCESS ))
                        {
                            RBUS_LOG_ERR("%s : rbus_registerMethodTable returns Err: %d",  __FUNCTION__, err);
                        }
                    }
                    else if(strcmp(component_id,"eRT.com.cisco.spvtg.ccsp.telemetry") == 0)
                    {
                        rbus_method_table_entry_t table[1] = {
                            {CCSP_TELEMETRY_DATA_SIGNAL, (void*)bus_info, telemetry_send_signal_rbus}, 
                        };
                        if(( err = rbus_registerMethodTable(component_id, table, 1) != RBUSCORE_SUCCESS ))
                        {
                            RBUS_LOG_ERR("%s : rbus_registerMethodTable returns Err: %d",  __FUNCTION__, err);
                        }
                    }
                }
            }
        }
        /*CID: 110434 Resource leak*/
        fclose(fp);
        return 0;
}

void 
CCSP_Message_Bus_Exit
(
    void *bus_handle
)
{
    CCSP_MESSAGE_BUS_INFO *bus_info = (CCSP_MESSAGE_BUS_INFO *)bus_handle;

    rbusCoreError_t err = RBUSCORE_SUCCESS;
    err = rbus_unregisterObj(bus_info->component_id);
    if(RBUSCORE_SUCCESS != err)
        CcspTraceError(("<%s>: rbus_unregisterObj for component %s fails with %d\n", __FUNCTION__, bus_info->component_id, err));
    int rc = rbus_close(bus_info->rbus_handle);
    if(RBUS_ERROR_SUCCESS != rc)
        CcspTraceError(("<%s>: rbus_close fails with %d\n", __FUNCTION__,rc));
    bus_info->freefunc(bus_info);
    bus_info = NULL;
}

void rbus_type_to_ccsp_type (rbusValueType_t typeVal, enum dataType_e *pType)
{
    switch(typeVal)
    {
        case RBUS_INT16:
        case RBUS_INT32:
            *pType = ccsp_int;
            break;
        case RBUS_UINT16:
        case RBUS_UINT32:
            *pType = ccsp_unsignedInt;
            break;
        case RBUS_INT64:
            *pType = ccsp_long;
            break;
        case RBUS_UINT64:
            *pType = ccsp_unsignedLong;
            break;
        case RBUS_SINGLE:
            *pType = ccsp_float;
            break;
        case RBUS_DOUBLE:
            *pType = ccsp_double;
            break;
        case RBUS_DATETIME:
            *pType = ccsp_dateTime;
            break;
        case RBUS_BOOLEAN:
            *pType = ccsp_boolean;
            break;
        case RBUS_CHAR:
        case RBUS_INT8:
            *pType = ccsp_int;
            break;
        case RBUS_UINT8:
        case RBUS_BYTE:
            *pType = ccsp_byte;
            break;
        case RBUS_STRING:
            *pType = ccsp_string;
            break;
        case RBUS_BYTES:
            *pType = ccsp_base64;
            break;
        case RBUS_PROPERTY:
        case RBUS_OBJECT:
        case RBUS_NONE:
        default:
            *pType = ccsp_none;
            break;
    }
    return;
}

void ccsp_handle_rbus_component_reply (void* bus_handle, rbusMessage msg, rbusValueType_t typeVal, enum dataType_e *pType, char** pStringValue)
{
    CCSP_MESSAGE_BUS_INFO *bus_info = (CCSP_MESSAGE_BUS_INFO *)bus_handle;
    int32_t ival = 0;
    int64_t i64 = 0;
    double fval = 0;
    const void *pValue = NULL;
    int length = 0;
    char *pTmp = NULL;
    int n = 0;
    rbus_type_to_ccsp_type(typeVal, pType);
    switch(typeVal)
    {
        case RBUS_INT16:
        case RBUS_INT32:
            rbusMessage_GetInt32(msg, &ival);
            n = snprintf(pTmp, 0, "%d", ival) + 1;
            *pStringValue = bus_info->mallocfunc(n);
            snprintf(*pStringValue, (unsigned int)n, "%d", ival);
            break;

        case RBUS_UINT16:
        case RBUS_UINT32:
            rbusMessage_GetInt32(msg, &ival);
            n = snprintf(pTmp, 0, "%u", (uint32_t)ival) + 1;
            *pStringValue = bus_info->mallocfunc(n);
            snprintf(*pStringValue, (unsigned int)n, "%u", (uint32_t)ival);
            break;

        case RBUS_INT64:
        {
            rbusMessage_GetInt64(msg, &i64);
#ifdef _64BIT_ARCH_SUPPORT_
            n = snprintf(pTmp, 0, "%ld", i64) + 1;
#else
            n = snprintf(pTmp, 0, "%lld", i64) + 1;
#endif
            *pStringValue = bus_info->mallocfunc(n);
#ifdef _64BIT_ARCH_SUPPORT_
            snprintf(*pStringValue, (unsigned int)n, "%ld", i64);
#else
            snprintf(*pStringValue, (unsigned int)n, "%lld", i64);
#endif	    
           break;
        }
        case RBUS_UINT64:
        {
            rbusMessage_GetInt64(msg, &i64);
#ifdef _64BIT_ARCH_SUPPORT_
            n = snprintf(pTmp, 0, "%lu", (uint64_t)i64) + 1;
#else
            n = snprintf(pTmp, 0, "%llu", (uint64_t)i64) + 1;
#endif
            *pStringValue = bus_info->mallocfunc(n);
#ifdef _64BIT_ARCH_SUPPORT_
            snprintf(*pStringValue, (unsigned int)n, "%lu", (uint64_t)i64);
#else	
            snprintf(*pStringValue, (unsigned int)n, "%llu", (uint64_t)i64);
#endif	    
            break;
        }
        case RBUS_SINGLE:
            rbusMessage_GetDouble(msg, &fval);
            n = snprintf(pTmp, 0, "%f", fval) + 1;
            *pStringValue = bus_info->mallocfunc(n);
            snprintf(*pStringValue, (unsigned int)n, "%f", fval);
            break;
        case RBUS_DOUBLE:
            rbusMessage_GetDouble(msg, &fval);
            n = snprintf(pTmp, 0, "%f", fval) + 1;
            *pStringValue = bus_info->mallocfunc(n);
            snprintf(*pStringValue, (unsigned int)n, "%f", fval);
            break;
        case RBUS_DATETIME:
        {
            rbusDateTime_t rbus_time = {{0},{0}};
            char tmpBuff[40] = {0};
            rbusMessage_GetBytes(msg, (uint8_t const**)&pValue, (uint32_t*)&length);
            memcpy(&rbus_time,pValue,sizeof(rbusDateTime_t));
            if(0 == rbus_time.m_time.tm_year) {
                snprintf(tmpBuff, sizeof(tmpBuff), "%04d-%02d-%02dT%02d:%02d:%02d", rbus_time.m_time.tm_year,
                                                                    rbus_time.m_time.tm_mon,
                                                                    rbus_time.m_time.tm_mday,
                                                                    rbus_time.m_time.tm_hour,
                                                                    rbus_time.m_time.tm_min,
                                                                    rbus_time.m_time.tm_sec);
            } else {
                /* tm_mon represents month from 0 to 11. So increment tm_mon by 1.
                   tm_year represents years since 1900. So add 1900 to tm_year.
                 */
                snprintf(tmpBuff, sizeof(tmpBuff), "%04d-%02d-%02dT%02d:%02d:%02d", rbus_time.m_time.tm_year+1900,
                                                                    rbus_time.m_time.tm_mon+1,
                                                                    rbus_time.m_time.tm_mday,
                                                                    rbus_time.m_time.tm_hour,
                                                                    rbus_time.m_time.tm_min,
                                                                    rbus_time.m_time.tm_sec);
            }
            n = snprintf(pTmp, 0, "0000-00-00T00:00:00+00:00") + 1;
            *pStringValue = bus_info->mallocfunc(n);
            if( rbus_time.m_tz.m_tzhour || rbus_time.m_tz.m_tzmin )
            {
                snprintf(*pStringValue, (unsigned int)n, "%s%c%02d:%02d", tmpBuff, (0 == rbus_time.m_tz.m_isWest) ? '+':'-', rbus_time.m_tz.m_tzhour, rbus_time.m_tz.m_tzmin);
            }
            else
            {
                snprintf(*pStringValue, (unsigned int)n, "%sZ", tmpBuff);
            }
        }
            break;
        case RBUS_BOOLEAN:
        {
            rbusMessage_GetBytes(msg, (uint8_t const**)&pValue, (uint32_t *)&length);
            unsigned char boolValue = *(unsigned char*)pValue;
            n = snprintf(pTmp, 0, "false") + 1;
            *pStringValue = bus_info->mallocfunc(n);
            snprintf(*pStringValue, (unsigned int)n, "%s", boolValue ? "true" : "false");
            break;
        }
        case RBUS_CHAR:
        case RBUS_INT8:
        {
            rbusMessage_GetBytes(msg, (uint8_t const**)&pValue, (uint32_t *)&length);
            signed char tmpValue = *(signed char*)pValue;
            n = snprintf(pTmp, 0, "%d", tmpValue) + 1;
            *pStringValue = bus_info->mallocfunc(n);
            snprintf(*pStringValue, (unsigned int)n, "%d", tmpValue);
            break;
        }
        case RBUS_UINT8:
        case RBUS_BYTE:
        {
            rbusMessage_GetBytes(msg, (uint8_t const**)&pValue, (uint32_t *)&length);
            unsigned char tmpValue = *(unsigned char*)pValue;
            n = snprintf(pTmp, 0, "%u", tmpValue) + 1;
            *pStringValue = bus_info->mallocfunc(n);
            snprintf(*pStringValue, (unsigned int)n, "%u", tmpValue);
            break;
        }
        case RBUS_STRING:
            rbusMessage_GetBytes(msg, (uint8_t const**)&pValue, (uint32_t *)&length);
            n = length + 1;
            *pStringValue = bus_info->mallocfunc(n);
            snprintf(*pStringValue, (unsigned int)n, "%s", (char*)pValue);
            break;
        case RBUS_BYTES:
        {
            int k = 0;
            unsigned char* pVar = NULL;
            char* pStrVar = NULL;
            unsigned char tmp = 0;
            rbusMessage_GetBytes(msg, (uint8_t const**)&pVar, (uint32_t *)&length);

            n = (2 * length) + 1;
            pStrVar = bus_info->mallocfunc(n);
            *pStringValue = pStrVar;
            for (k = 0; k < length; k++)
            {
                tmp = pVar[k];
                snprintf (&pStrVar[k * 2], (unsigned int)n, "%02X", tmp);
            }
            break;
        }
        case RBUS_PROPERTY:
        case RBUS_OBJECT:
        case RBUS_NONE:
        default:
            *pStringValue = bus_info->mallocfunc(10);
            strncpy(*pStringValue, "", 10);
            break;
    }
    
    return;
}

unsigned int get_writeid(const char *str)
{
    if ( _ansc_strcmp(str, "ccsp.busclient" ) == 0 )
        return DSLH_MPA_ACCESS_CONTROL_CLIENTTOOL;
    else if ( _ansc_strcmp(str, "ccsp.cisco.spvtg.ccsp.snmp" ) == 0 )
        return DSLH_MPA_ACCESS_CONTROL_SNMP;
    else if ( _ansc_strcmp(str, "com.cisco.spvtg.ccsp.lms") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_LM;
    else if ( _ansc_strcmp(str, "com.cisco.spvtg.ccsp.wifi") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_WIFI;
    else
        return  DSLH_MPA_ACCESS_CONTROL_ACS;
}

char* writeid_to_string(unsigned int writeid)
{
    if(writeid == DSLH_MPA_ACCESS_CONTROL_WEBUI)
        return "ccsp.phpextension";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_SNMP)
        return "ccsp.cisco.spvtg.ccsp.snmp";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_ACS)
        return "eRT.com.cisco.spvtg.ccsp.tr069pa";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_CLI)
        return "writeid_cli";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_WEBPA)
        return "com.cisco.spvtg.ccsp.webpaagent";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_XPC)
        return "writeid_xpc";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_NOTIFY_COMP)
        return "eRT.com.cisco.spvtg.ccsp.notifycomponent";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_PAM)
        return "eRT.com.cisco.spvtg.ccsp.pam";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_CLIENTTOOL)
        return "ccsp.busclient";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_LM)
        return "com.cisco.spvtg.ccsp.lms";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_WIFI)
        return "eRT.com.cisco.spvtg.ccsp.wifi";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_XMPP)
        return "writeid_xmpp";
    else if(writeid == DSLH_MPA_ACCESS_CONTROL_WEBCONFIG)
        return "webconfig";
    else
        return "writeid_cli";
}

unsigned int string_to_writeid(const char *str)
{
    if ( _ansc_strcmp(str, "ccsp.phpextension") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_WEBUI;
    else if ( _ansc_strcmp(str, "ccsp.cisco.spvtg.ccsp.snmp") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_SNMP;
    else if ( _ansc_strcmp(str, "eRT.com.cisco.spvtg.ccsp.tr069pa") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_ACS;
    else if ( _ansc_strcmp(str, "writeid_cli") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_CLI;
    else if ( (_ansc_strcmp(str, "eRT.com.cisco.spvtg.ccsp.webpaagent") == 0 )
                || (_ansc_strcmp(str, "com.cisco.spvtg.ccsp.webpaagent") == 0))
        return DSLH_MPA_ACCESS_CONTROL_WEBPA;
    else if ( _ansc_strcmp(str, "writeid_xpc") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_XPC;
    else if ( _ansc_strcmp(str, "eRT.com.cisco.spvtg.ccsp.notifycomponent") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_NOTIFY_COMP;
    else if ( _ansc_strcmp(str, "eRT.com.cisco.spvtg.ccsp.pam") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_PAM;
    else if ( _ansc_strcmp(str, "ccsp.busclient") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_CLIENTTOOL;
    else if ( _ansc_strcmp(str, "com.cisco.spvtg.ccsp.lms") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_LM;
    else if ( _ansc_strcmp(str, "eRT.com.cisco.spvtg.ccsp.wifi") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_WIFI;
    else if ( _ansc_strcmp(str, "writeid_xmpp") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_XMPP;
    else if ( _ansc_strcmp(str, "webconfig") == 0 )
        return DSLH_MPA_ACCESS_CONTROL_WEBCONFIG;
     return DSLH_MPA_ACCESS_CONTROL_CLI;
}

void get_recursive_wildcard_parameterNames(void* bus_handle, char *parameterName, rbusMessage *req, int *param_size)
{
    CCSP_MESSAGE_BUS_INFO *bus_info = (CCSP_MESSAGE_BUS_INFO *)bus_handle;
    CCSP_Base_Func_CB* func = (CCSP_Base_Func_CB* )bus_info->CcspBaseIf_func;
    int result = 0, i = 0, tmp;
    int wild_param_size = 0;
    char* context = NULL;
    parameterInfoStruct_t **info = 0;
    rbusMessage msg = NULL;
    if (req != NULL && *req != NULL)
    {
        msg = (*req);
    }

    char *token1 = strtok_r(parameterName, "*", &context);
    char *token2 = strtok_r(NULL, "", &context);

    if (!token1 || !token2 )
    {
        return;
    }

    if (func->getParameterNames && msg)
    {
        result = func->getParameterNames(token1, 1, &wild_param_size, &info, func->getParameterNames_data);
        tmp = result;
        if((tmp == CCSP_SUCCESS) && info)
        {
            for (i = 0; i < wild_param_size; i++)
            {
                char fullName[RBUS_MAX_NAME_LENGTH] = {0};
                char* tmpPtr = NULL;
                snprintf(fullName, RBUS_MAX_NAME_LENGTH, "%s%s", info[i]->parameterName, token2+1);
                tmpPtr = strstr (fullName, "*");
                if (tmpPtr)
                {
                    get_recursive_wildcard_parameterNames(bus_info, fullName, &msg, param_size);
                }
                else
                {
                    rbusMessage_SetString(msg, fullName);
                    *param_size = (*param_size)+1;
                }
            }
            free_parameterInfoStruct_t(bus_info, wild_param_size, info);
        }
    }
}

static int thread_path_message_func_rbus(const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr)
{
    UNREFERENCED_PARAMETER(destination);
    CCSP_MESSAGE_BUS_INFO *bus_info = (CCSP_MESSAGE_BUS_INFO *)user_data;

    CCSP_Base_Func_CB* func = (CCSP_Base_Func_CB* )bus_info->CcspBaseIf_func;
    CcspTraceDebug(("%s Component ID: %s method: %s reply_topic:%s\n", __FUNCTION__, bus_info->component_id, method, hdr->reply_topic));
    if(NULL != method && func != NULL)
    {
        if(!strncmp(method, METHOD_GETPARAMETERVALUES, MAX_METHOD_NAME_LENGTH) && func->getParameterValues)
        {
            int result = 0, i =0, size =0;
            char **parameterNames = 0;
            unsigned int writeID = DSLH_MPA_ACCESS_CONTROL_ACS;
            const char *writeID_str = NULL;
            int32_t param_size = 0, tmp = 0;
            parameterValStruct_t **val = 0;
            rbusMessage req;
            if(rbusMessage_GetString(request, &writeID_str) == RT_OK)
                writeID = get_writeid(writeID_str);
            rbusMessage_GetInt32(request, &size);
            rbusMessage_Init(&req);

            for(i = 0; i < size; i++)
            {
                char *param_name = 0;
                char* tmpPtr = NULL;
                rbusMessage_GetString(request, (const char**)&param_name);
                /* wildcard */
                tmpPtr = strstr (param_name, "*");
                if (tmpPtr)
                {
                    get_recursive_wildcard_parameterNames(bus_info,  param_name, &req, &param_size);
                }
                else
                {
                    rbusMessage_SetString(req, param_name);
                    param_size++;
                }
            }

            if(param_size > 0)
            {
                parameterNames = bus_info->mallocfunc(param_size*sizeof(char *));
                memset(parameterNames, 0, param_size*sizeof(char *));
            }
            for(i = 0; i < param_size; i++)
            {
                parameterNames[i] = NULL;
                if (req)
                {
                    rbusMessage_GetString(req, (const char**)&parameterNames[i]);
                    CcspTraceDebug(("parameterNames[%d]: %s\n", i, parameterNames[i]));
                }
            }

            size = 0;
            if (parameterNames != NULL)
            {
                result = func->getParameterValues(writeID, parameterNames, param_size, &size, &val , func->getParameterValues_data);
                CcspTraceDebug(("getParameterValues: size %d result %d\n", size, result));
                bus_info->freefunc(parameterNames);
                rbusMessage_Release(req);

                rbusMessage_Init(response);
                tmp = result;
                rbusMessage_SetInt32(*response, tmp); //result
                if(tmp == CCSP_SUCCESS )
                {
                    rbusMessage_SetInt32(*response, size);
                    for(i = 0; i < size; i++)
                    {
                        CcspTraceDebug(("val[%d]->parameterName %s val[%d]->parameterValue %s\n", i, val[i]->parameterName, i, val[i]->parameterValue));
                        rbusMessage_SetString(*response, val[i]->parameterName);
                        rbusMessage_SetInt32(*response, val[i]->type);
                        rbusMessage_SetString(*response, val[i]->parameterValue);
                    }
                }
                free_parameterValStruct_t(bus_info, size, val);
            }
        }
        else if(!strncmp(method, METHOD_GETHEALTH, MAX_METHOD_NAME_LENGTH) && func->getHealth)
        {
            int32_t result = 0;
            result = func->getHealth();
            rbusMessage_Init(response);
            rbusMessage_SetInt32(*response, result);
            CcspTraceDebug(("exiting METHOD_GETHEALTH with result %d\n", result));
            return DBUS_HANDLER_RESULT_HANDLED;
        }
        else if(!strncmp(method, METHOD_SETPARAMETERVALUES, MAX_METHOD_NAME_LENGTH) && func->setParameterValues)
        {
            int param_size = 0, i = 0, result = 0;
            parameterValStruct_t * parameterVal = 0;
            unsigned int writeID = DSLH_MPA_ACCESS_CONTROL_CLI;
            const char * writeID_str = NULL;
            int32_t sessionId = 0, tmp = 0;
            dbus_bool commit = 0;
            char *invalidParameterName = 0;
            int32_t dataType = 0;
            char *tmpParamVal = NULL;

            rbusMessage_GetInt32(request, &sessionId);
            if(rbusMessage_GetString(request, &writeID_str) == RT_OK)
                writeID = string_to_writeid(writeID_str);
            rbusMessage_GetInt32(request, (int32_t*)&param_size);
            if(param_size > 0)
            {
                parameterVal = bus_info->mallocfunc(param_size*sizeof(parameterValStruct_t ));
                memset(parameterVal, 0, param_size*sizeof(parameterValStruct_t ));
            }

            for(i = 0; i < param_size; i++)
            {
                parameterVal[i].parameterName = NULL;
                parameterVal[i].parameterValue = NULL;
                rbusMessage_GetString(request, (const char**)&parameterVal[i].parameterName);
                rbusMessage_GetInt32(request, &dataType);
                if (dataType < RBUS_BOOLEAN)
                {
                    parameterVal[i].type = dataType;
                    rbusMessage_GetString(request, (const char**)&tmpParamVal);
                    if(tmpParamVal)
                    {
                        parameterVal[i].parameterValue = bus_info->mallocfunc((strlen(tmpParamVal)+1));
                        if(parameterVal[i].parameterValue)
                        {
                            memset(parameterVal[i].parameterValue,0,(strlen(tmpParamVal)+1));
                            strncpy(parameterVal[i].parameterValue,tmpParamVal,strlen(tmpParamVal));
                        }
                    }
                }
                else
                {
                    ccsp_handle_rbus_component_reply (bus_info, request, (rbusValueType_t) dataType, &parameterVal[i].type, &parameterVal[i].parameterValue);
                }
            }
            const char *str = NULL;
            rbusMessage_GetString(request, &str); //commit
            commit = (str && strcasecmp(str, "TRUE") == 0)?1:0;
            result = func->setParameterValues(sessionId, writeID, parameterVal, param_size, commit,&invalidParameterName, func->setParameterValues_data);
            CcspTraceDebug(("setParameterValues result %d\n", result));
            rbusMessage_Init(response);
            tmp = result;
            rbusMessage_SetInt32(*response, tmp); //result
            if(invalidParameterName != NULL)
                rbusMessage_SetString(*response, invalidParameterName); //invalid param
            else
                rbusMessage_SetString(*response, ""); //invalid param

            for(i = 0; i < param_size; i++)
            {
                if(parameterVal[i].parameterValue)
                {
                    bus_info->freefunc(parameterVal[i].parameterValue);
                }
            }

            bus_info->freefunc(parameterVal);
            bus_info->freefunc(invalidParameterName);
            return DBUS_HANDLER_RESULT_HANDLED;
        }
        else if(!strncmp(method, METHOD_GETPARAMETERATTRIBUTES, MAX_METHOD_NAME_LENGTH) && func->getParameterAttributes)
        {
            char **parameterNames = 0;
            parameterAttributeStruct_t **val = 0;
            int size = 0, result = 0, i = 0, param_size = 0;
            int32_t tmp = 0;
            rbusMessage_GetInt32(request, &param_size);

            if(param_size)
            {
                parameterNames = bus_info->mallocfunc(param_size*sizeof(char *));
                memset(parameterNames, 0, param_size*sizeof(char *));
            }

            for(i = 0; i < param_size; i++)
            {
                parameterNames[i] = NULL;
                rbusMessage_GetString(request, (const char**)&parameterNames[i]);
                CcspTraceDebug(("parameterNames[%d]: %s\n", i, parameterNames[i]));
            }

            size = 0;
            result = func->getParameterAttributes(parameterNames, param_size, &size, &val , func->getParameterAttributes_data);
            bus_info->freefunc(parameterNames);
            rbusMessage_Init(response);
            tmp = result;
            rbusMessage_SetInt32(*response, tmp);
            if( tmp == CCSP_SUCCESS )
            {
                rbusMessage_SetInt32(*response, (int32_t)size);

                for(i = 0; i < size; i++)
                {
                    rbusMessage_SetString(*response, val[i]->parameterName);
                    rbusMessage_SetInt32(*response, val[i]->notificationChanged);
                    rbusMessage_SetInt32(*response, val[i]->notification);
                    rbusMessage_SetInt32(*response, val[i]->accessControlChanged);
                    rbusMessage_SetInt32(*response, val[i]->access);
                    rbusMessage_SetInt32(*response, val[i]->accessControlBitmask);
                }
            }
            free_parameterAttributeStruct_t(bus_info, size, val);
            return DBUS_HANDLER_RESULT_HANDLED;
        }
        else if(!strncmp(method, METHOD_COMMIT, MAX_METHOD_NAME_LENGTH) && func->setCommit)
        {
            int32_t tmp = 0, sessionId = 0, commit = 0;
            unsigned int writeID = DSLH_MPA_ACCESS_CONTROL_CLI;
            const char * writeID_str = NULL;
            int result = 0;
            rbusMessage_GetInt32(request, &sessionId);
            if(rbusMessage_GetString(request, &writeID_str) == RT_OK)
                writeID = string_to_writeid(writeID_str);
            rbusMessage_GetInt32(request, &commit);
            result = func->setCommit(sessionId, writeID, commit, func->setCommit_data);
            rbusMessage_Init(response);
            tmp = result;
            rbusMessage_SetInt32(*response, tmp); //result
            return DBUS_HANDLER_RESULT_HANDLED;
        }
        else if(!strncmp(method, METHOD_SETPARAMETERATTRIBUTES, MAX_METHOD_NAME_LENGTH) && func->setParameterAttributes)
        {
            parameterAttributeStruct_t * parameterAttribute = 0;
            int i = 0, sessionId = 0, param_size = 0, result = 0, tmp = 0;
            rbusMessage_GetInt32(request, &sessionId);
            rbusMessage_GetInt32(request, &param_size);
            if(param_size > 0)
            {
                parameterAttribute = bus_info->mallocfunc(param_size*sizeof(parameterAttributeStruct_t));
                memset(parameterAttribute, 0, param_size*sizeof(parameterAttributeStruct_t));
            }
            for(i = 0; i < param_size; i++)
            {
                rbusMessage_GetString(request, (const char**)&parameterAttribute[i].parameterName);
                rbusMessage_GetInt32(request, (int32_t*)&parameterAttribute[i].notificationChanged);
                rbusMessage_GetInt32(request, (int32_t*)&parameterAttribute[i].notification);
                rbusMessage_GetInt32(request, (int32_t*)&parameterAttribute[i].access);
                rbusMessage_GetInt32(request, (int32_t*)&parameterAttribute[i].accessControlChanged);
                rbusMessage_GetInt32(request, (int32_t*)&parameterAttribute[i].accessControlBitmask);
                rbusMessage_GetInt32(request, (int32_t*)&parameterAttribute[i].RequesterID);
            }
            result = func->setParameterAttributes(sessionId, parameterAttribute, param_size, func->setParameterAttributes_data);
            rbusMessage_Init(response);
            tmp = result;
            rbusMessage_SetInt32(*response, tmp); //result
            bus_info->freefunc(parameterAttribute);
            return DBUS_HANDLER_RESULT_HANDLED;
        }
        else if(!strncmp(method, METHOD_GETPARAMETERNAMES, MAX_METHOD_NAME_LENGTH) && func->getParameterNames)
        {
            int i = 0,size = 0;
            int32_t requestedDepth, rowNamesOnly = 0, result = 0, tmp = 0;
            char * parameterName = 0;
            parameterInfoStruct_t **val = 0;
            rbusMessage_GetString(request, (const char**)&parameterName);
            rbusMessage_GetInt32(request, &requestedDepth); 
            rbusMessage_GetInt32(request, &rowNamesOnly);
            rbusMessage_Init(response);
            result = func->getParameterNames(parameterName, requestedDepth == -1, &size, &val, func->getParameterNames_data );
            tmp = result;
            rbusMessage_SetInt32(*response, tmp); //result
            if( tmp == CCSP_SUCCESS)
            {
                int actualCount = 0;
                char buf[CCSP_BASE_PARAM_LENGTH];
                int inst_num;
                int type;
                                
                if(rowNamesOnly)
                {
                    for(i = 0; i < size; i++)
                    {
                        type = CcspBaseIf_getObjType(parameterName, val[i]->parameterName, &inst_num, buf);
                        if(type == CCSP_BASE_INSTANCE)
                            actualCount++;
                    }
                }
                else
                {
                    actualCount = size;
                }

                rbusMessage_SetInt32(*response, actualCount);

                for(i = 0; i < size; i++)
                {
                    
                    type = CcspBaseIf_getObjType(parameterName, val[i]->parameterName, &inst_num, buf);

                    CcspTraceDebug(("Param [%d] Name=%s, Writable=%d, Type=%d\n", i, val[i]->parameterName, val[i]->writable, type));

                    if(rowNamesOnly)
                    {
                        if(type != CCSP_BASE_INSTANCE)
                            continue;
                        rbusMessage_SetInt32(*response, (int32_t)inst_num); /*instancen number*/    
                        rbusMessage_SetString(*response, ""); /*alias -- which is unsupported in ccsp*/    
                    }
                    else
                    {
                        rbusElementType_t elemType = 0;
                        rbusAccess_t accessFlags = 0;

                        /* determine element type */
                        if(type == CCSP_BASE_PARAM)
                        {
                            elemType = RBUS_ELEMENT_TYPE_PROPERTY;
                        }
                        else if(type == CCSP_BASE_INSTANCE)
                        {
                            elemType = 0; /*object*/
                        }
                        else if(type == CCSP_BASE_OBJECT)
                        {
                            /*there's no way to know completely if its a table or a plain object
                              the writable flag can be true for some table types but not all 
                              so the following might set static and dynamic tables (which are both read-only tables) to type object*/
                            if(val[i]->writable)
                                elemType = RBUS_ELEMENT_TYPE_TABLE;
                            else
                                elemType = 0;/*object*/
                        }

                        /* determine access flags */
                        accessFlags = RBUS_ACCESS_GET; /*can read everything */

                        if(elemType == RBUS_ELEMENT_TYPE_PROPERTY)
                        {
                            accessFlags |=  RBUS_ACCESS_SUBSCRIBE;  /*can subscribe to value-change events*/
                            if(val[i]->writable)
                                accessFlags |= RBUS_ACCESS_SET;
                        }
                        else if(elemType == RBUS_ELEMENT_TYPE_TABLE)
                        {
                            if(val[i]->writable)
                                accessFlags |= RBUS_ACCESS_ADDROW | RBUS_ACCESS_REMOVEROW;
                        }
                        else /*objects or rows*/
                        {   
                            if(val[i]->writable)
                                accessFlags |= RBUS_ACCESS_SET;
                        }

                        rbusMessage_SetString(*response, val[i]->parameterName);
                        rbusMessage_SetInt32(*response, (int32_t)elemType);
                        rbusMessage_SetInt32(*response, (int32_t)accessFlags);
                    }
                }
            }
            free_parameterInfoStruct_t(bus_info, size, val);
        }
        else if (!strncmp(method, METHOD_ADDTBLROW, MAX_METHOD_NAME_LENGTH) && func->AddTblRow)
        {
            int instanceNumber = 0, result = 0;
            int32_t tmp = 0, sessionId = 0;
            char *str = 0;
            rbusMessage_GetInt32(request, &sessionId);
            rbusMessage_GetString(request, (const char**)&str); //object name
            result = func->AddTblRow(sessionId, str, &instanceNumber , func->AddTblRow_data);
            rbusMessage_Init(response);
            tmp = result;
            rbusMessage_SetInt32(*response, tmp); //result
            tmp = instanceNumber;
            rbusMessage_SetInt32(*response, tmp); //inst num
            return DBUS_HANDLER_RESULT_HANDLED;
        }
        else if (!strncmp(method, METHOD_DELETETBLROW, MAX_METHOD_NAME_LENGTH) && func->DeleteTblRow)
        {
            int result = 0;
            int32_t tmp = 0, sessionId = 0;
            char * str = 0;
            rbusMessage_GetInt32(request, &sessionId);
            rbusMessage_GetString(request, (const char**)&str); //obj name
            result = func->DeleteTblRow(sessionId, str , func->DeleteTblRow_data);
            rbusMessage_Init(response);
            tmp = result;
            rbusMessage_SetInt32(*response, tmp); //result
            return DBUS_HANDLER_RESULT_HANDLED;
        }
        else if (!strcmp(method, CCSP_PARAMETER_VALUE_CHANGE_SIGNAL) && func->parameterValueChangeSignal)
        {
            parameterSigStruct_t *val = 0;
            int param_size = 0, i = 0;

            rbusMessage_GetInt32(request, (int32_t*)&param_size);

            if(param_size)
            {
                val = bus_info->mallocfunc(param_size*sizeof(parameterSigStruct_t ));
                memset(val, 0, param_size*sizeof(parameterSigStruct_t ));

                for(i = 0; i < param_size; i++)
                {
                    rbusMessage_GetString(request, &val[i].parameterName);
                    rbusMessage_GetString(request, &val[i].oldValue);
                    rbusMessage_GetString(request, &val[i].newValue);
                    rbusMessage_GetInt32(request, (int32_t*)&val[i].type);
                    rbusMessage_GetString(request, &val[i].subsystem_prefix);
                    rbusMessage_GetInt32(request, (int32_t*)&val[i].writeID);
                }

                func->parameterValueChangeSignal(val, param_size,func->parameterValueChangeSignal_data);

                bus_info->freefunc(val);
            }
        }
        else if((!strncmp(method, METHOD_SUBSCRIBE, MAX_METHOD_NAME_LENGTH)) || (!strncmp(method, METHOD_UNSUBSCRIBE, MAX_METHOD_NAME_LENGTH)))
        {
            const char * sender = NULL;
            const char * eventName = NULL;
            int has_payload = 0;
            rbusMessage payload = NULL;
            int32_t componentId = 0;
            int32_t interval = 0;
            int32_t duration = 0;
            int publishOnSubscribe = 0;
            int rawData = 0;
            rbusFilter_t filter = NULL;
            int size = 0;
            char* tmpPtr = NULL;
            int32_t param_size = 0;
            bool is_wildcard_query = false;
            int i;
            rbusMessage req;
            rbusCoreError_t err = RBUSCORE_SUCCESS;

            rbusMessage_Init(response);

            if((RT_OK == rbusMessage_GetString(request, &eventName)) &&
                    (RT_OK == rbusMessage_GetString(request, &sender)))
            {
                /*Extract arguments*/
                if((NULL == sender) || (NULL == eventName))
                {
                    RBUS_LOG_ERR("Malformed subscription request. Sender: %s. Event: %s.", sender, eventName);
                    rbusMessage_SetInt32(*response, RBUSCORE_ERROR_INVALID_PARAM);
                }
                else
                {
                    rbusMessage_GetInt32(request, &has_payload);
                    if(has_payload)
                        rbusMessage_GetMessage(request, &payload);
                    if(payload)
                    {
                        Ccsp_Rbus_ReadPayload(payload, &componentId, &interval, &duration, &filter);
                    }
                    else
                    {
                        RBUS_LOG_ERR("payload missing in subscribe request for event %s from %s", eventName, sender);
                    }
                    int added = strncmp(method, METHOD_SUBSCRIBE, MAX_METHOD_NAME_LENGTH) == 0 ? 1 : 0;

                    rbusMessage_GetInt32(request, &publishOnSubscribe);
                    rbusMessage_GetInt32(request, &rawData);
                    if(rawData)
                    {
                        err = RBUSCORE_ERROR_INVALID_PARAM;
                        rbusMessage_SetInt32(*response, err);
                    }
                    else
                    {
                        rbusMessage_Init(&req);
                        /* Handling Wildcard subscription */
                        tmpPtr = strstr (eventName, "*");
                        if (tmpPtr)
                        {
                            char paramName[RBUS_MAX_NAME_LENGTH] = {0};
                            snprintf(paramName, RBUS_MAX_NAME_LENGTH, "%s", (char *)eventName);
                            get_recursive_wildcard_parameterNames(bus_info, paramName, &req, &param_size);
                            is_wildcard_query = true;
                        }
                        else
                        {
                            rbusMessage_SetString(req, eventName);
                            param_size++;
                        }

                        rbusObject_t data = NULL;
                        rbusProperty_t tmpProperties = NULL;
                        rbusObject_Init(&data, NULL);
                        for (i = 0; i < param_size; i++)
                        {
                            char *parameter_name = 0;
                            rbusMessage_GetString(req, (const char**)&parameter_name);

                            /* Handling interval based subscription */
                            if (interval)
                            {
                                if (i == 0)
                                {
                                    err = cssp_event_subscribe_override_handler_rbus(NULL, parameter_name, eventName,
                                            sender, added, componentId, interval, duration, filter, user_data);
                                }
                            }
                            else
                            {
                                err = cssp_event_subscribe_override_handler_rbus(NULL, parameter_name, eventName,
                                        sender, added, componentId, interval, duration, filter, user_data);
                            }
                            if (i == 0)
                            {
                                rbusMessage_SetInt32(*response, err);

                            }
                            /* Handling Intial value */
                            if(publishOnSubscribe)
                            {
                                /*get wildcard qurey initial value*/
                                if (is_wildcard_query)
                                {
                                    if (i == 0)
                                    {
                                        rbusProperty_Init(&tmpProperties, "numberOfEntries", NULL);
                                        rbusProperty_SetInt32(tmpProperties, param_size);
                                    }
                                    parameterValStruct_t **val = 0;
                                    unsigned int writeID = DSLH_MPA_ACCESS_CONTROL_ACS;
                                    size = 0;
                                    if (func->getParameterValues)
                                    {
                                        err = func->getParameterValues(writeID, (char **)&parameter_name, 1, &size, &val , func->getParameterValues_data);
                                        rbusProperty_AppendString(tmpProperties, parameter_name, val[0]->parameterValue);
                                        free_parameterValStruct_t(bus_info, size, val);
                                    }
                                }
                                else
                                {
                                    size_t slen = 0;
                                    //determine if parameter_name is a parameter or partial path which is used for table identification
                                    slen = strlen(parameter_name);
                                    if ((parameter_name[slen-1] == '.') && (func->getParameterNames))
                                    {
                                        int j = 0;
                                        unsigned int requestedDepth = 1;
                                        int32_t result = 0;
                                        parameterInfoStruct_t **val = 0;
                                        size = 0;
                                        result = func->getParameterNames((char*)parameter_name, requestedDepth, &size, &val, func->getParameterNames_data);
                                        if( result == CCSP_SUCCESS)
                                        {
                                            char buf[CCSP_BASE_PARAM_LENGTH] = {0};
                                            int inst_num = 0;
                                            int type = 0;
                                            rbusProperty_Init(&tmpProperties, "numberOfEntries", NULL);
                                            if(size != 0)
                                            {
                                                for(j = 0; j < size; j++)
                                                {
                                                    char fullName[RBUS_MAX_NAME_LENGTH] = {0};
                                                    char row_instance[RBUS_MAX_NAME_LENGTH] = {0};
                                                    type = CcspBaseIf_getObjType((char *)parameter_name, val[j]->parameterName, &inst_num, buf);
                                                    if(type != CCSP_BASE_INSTANCE)
                                                        continue;
                                                    snprintf(fullName, RBUS_MAX_NAME_LENGTH, "%s%d.", parameter_name, inst_num);
                                                    if(j == 0)
                                                    {
                                                        rbusProperty_SetInt32(tmpProperties, size);
                                                    }
                                                    snprintf(row_instance, RBUS_MAX_NAME_LENGTH, "path%d", inst_num);
                                                    rbusProperty_AppendString(tmpProperties, row_instance, fullName);
                                                }
                                            }
                                            else
                                            {
                                                rbusProperty_SetInt32(tmpProperties, size);
                                            }
                                        }
                                        free_parameterInfoStruct_t(bus_info, size, val);
                                    }
                                    else
                                    {
                                        if(func->getParameterValues)
                                        {
                                            parameterValStruct_t **val = 0;
                                            rbusValue_t value = NULL;
                                            rbusValue_Init(&value);
                                            unsigned int writeID = DSLH_MPA_ACCESS_CONTROL_ACS;
                                            size = 0;
                                            err = func->getParameterValues(writeID, (char **)&parameter_name, 1, &size, &val , func->getParameterValues_data);
                                            rbusValue_SetString(value, val[0]->parameterValue);
                                            rbusObject_SetValue(data, "initialValue", value);
                                            rbusValue_Release(value);
                                            free_parameterValStruct_t(bus_info, size, val);
                                        }
                                        else
                                        {
                                            err = RBUS_ERROR_INVALID_OPERATION;
                                            rbusMessage_SetInt32(*response, 0); /* No initial value returned, as get handler is not present */
                                            RBUS_LOG_ERR("Get handler does not exist %s", parameter_name);
                                        }
                                    }
                                }

                                if (i == (param_size-1))
                                {
                                    if (tmpProperties)
                                    {
                                        rbusObject_SetProperty(data, tmpProperties);
                                    }
                                    rbusEvent_t event = {0};
                                    event.name = eventName; /* use the same eventName the consumer subscribed with */
                                    event.type = RBUS_EVENT_INITIAL_VALUE;
                                    event.data = data;
                                    rbusMessage_SetInt32(*response, 1); /* Based on this value initial value will be published to the consumer */
                                    rbusEventData_appendToMessage(&event, filter, interval, duration, componentId, *response);
                                }
                            }
                        }

                        if(req)
                            rbusMessage_Release(req);
                        rbusObject_Release(data);
                        rbusProperty_Release(tmpProperties);
                    }
                    if(payload)
                    {
                        if(filter)
                        {
                            rbusFilter_Release(filter);
                        }
                        rbusMessage_Release(payload);
                    }
                    rbusMessage_SetInt32(*response, 0); /* Setting the subscriptionId to 0 as it is not used in ccsp */
                }
            }
        }
    }
    return 0;
}

static int webcfg_signal_rbus(const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr)
{
    UNREFERENCED_PARAMETER(response);
    (void) destination;
    (void) method;
    (void) hdr;
    int err = CCSP_Message_Bus_OK;
    CCSP_MESSAGE_BUS_INFO *bus_info =(CCSP_MESSAGE_BUS_INFO *) user_data;
    CCSP_Base_Func_CB* func = (CCSP_Base_Func_CB* )bus_info->CcspBaseIf_func;

    RBUS_LOG ("%s Received %s", __FUNCTION__, method);
    if ((func) && (func->webconfigSignal))
    {
        char* webconfig_data = 0;
        RBUS_LOG_ERR("Handling : %s from Component: %s", method, bus_info->component_id);
        rbusMessage_GetString(request, (char const**)&webconfig_data);
        func->webconfigSignal(webconfig_data, func->webconfigSignal_data);
    }
    return err;
}

static int tunnelStatus_signal_rbus(const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr)
{
    UNREFERENCED_PARAMETER(response);
    (void) destination;
    (void) method;
    (void) hdr;
    int err = CCSP_Message_Bus_OK;
    CCSP_MESSAGE_BUS_INFO *bus_info =(CCSP_MESSAGE_BUS_INFO *) user_data;
    CCSP_Base_Func_CB* func = (CCSP_Base_Func_CB* )bus_info->CcspBaseIf_func;

    RBUS_LOG ("%s Received %s", __FUNCTION__, method);
    if (func->TunnelStatus)
    {
        char* tunnel_status = 0;
        RBUS_LOG_ERR("Handling : %s from Component: %s", method, bus_info->component_id);
        rbusMessage_GetString(request, (char const**)&tunnel_status);
        func->TunnelStatus(tunnel_status, func->TunnelStatus_data);
    }
    return err;
}

static int wifiDbStatus_signal_rbus(const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr)
{
    UNREFERENCED_PARAMETER(response);
    (void) destination;
    (void) method;
    (void) hdr;
    int err = CCSP_Message_Bus_OK;
    CCSP_MESSAGE_BUS_INFO *bus_info =(CCSP_MESSAGE_BUS_INFO *) user_data;
    CCSP_Base_Func_CB* func = (CCSP_Base_Func_CB* )bus_info->CcspBaseIf_func;

    RBUS_LOG ("%s Received %s", __FUNCTION__, method);
    if ((func) && (func->WifiDbStatus))
    {
        char* wifidb_status = 0;
        RBUS_LOG_ERR("Handling : %s from Component: %s", method, bus_info->component_id);
        rbusMessage_GetString(request, (char const**)&wifidb_status);
        func->WifiDbStatus(wifidb_status, func->WifiDbStatus_data);
    }
    return err;
}

static int telemetry_send_signal_rbus(const char * destination, const char * method, rbusMessage request, void * user_data, rbusMessage *response, const rtMessageHeader* hdr)
{
    UNREFERENCED_PARAMETER(response);
    (void) destination;
    (void) method;
    (void) hdr;
    int err = CCSP_Message_Bus_OK;
    char* telemetry_data = NULL;
    CCSP_MESSAGE_BUS_INFO *bus_info =(CCSP_MESSAGE_BUS_INFO *) user_data;
    CCSP_Base_Func_CB* func = (CCSP_Base_Func_CB* )bus_info->CcspBaseIf_func;

    if ((func) && (func->telemetryDataSignal))
    {
        rbusMessage_GetString(request, (const char**)&telemetry_data);
        func->telemetryDataSignal(telemetry_data,func->telemetryDataSignal_data);
    }
    return err;
}
static int
CCSP_Message_Bus_Register_Path_Priv_rbus
(
 void* bus_handle,
 rbus_callback_t funcptr,
 void * user_data
)
{
    UNREFERENCED_PARAMETER(user_data);
    CCSP_MESSAGE_BUS_INFO *bus_info = (CCSP_MESSAGE_BUS_INFO *)bus_handle;
    bus_info->rbus_callback = (void *)funcptr;
    return CCSP_Message_Bus_OK;
}

static void Ccsp_Rbus_ReadPayload(
    rbusMessage payload,
    int32_t* componentId,
    int32_t* interval,
    int32_t* duration,
    rbusFilter_t* filter)
{
    *componentId = 0;
    *interval = 0;
    *duration = 0;
    *filter = NULL;
    if(payload)
    {
        int hasFilter;
        rbusMessage_GetInt32(payload, componentId);
        rbusMessage_GetInt32(payload, interval);
        rbusMessage_GetInt32(payload, duration);
        rbusMessage_GetInt32(payload, &hasFilter);
        if(hasFilter)
            rbusFilter_InitFromMessage(filter, payload);
    }
}

/*
 *  Added to support rbus value-change detection
 *  This will check if eventName refers to a parameter (and not an event like CCSP_SYSTEM_READY_SIGNAL)
 *  If its a parameter it will assume value-change is desired and pass the data to Ccsp_RbusValueChange api to handle it
 */
static int cssp_event_subscribe_override_handler_rbus(
    char const* object,
    char const* paramName,
    char const* eventName,
    char const* listener,
    int added,
    int componentId,
    int interval,
    int duration,
    rbusFilter_t filter,
    void* userData)
{
    size_t slen;
    (void)object;

    //determine if eventName is a parameter
    slen = strlen(eventName);
    if(slen < 7 || strncmp(eventName, "Device.", 7) != 0 || eventName[slen-1] == '!')
    {
        //not a parameter so return special error so rbus_core will search its registered event list for actual events like CCSP_SYSTEM_READY_SIGNAL
        CcspTraceWarning(("%s: ignored %s\n", __FUNCTION__, eventName));
        return RBUSCORE_ERROR_SUBSCRIBE_NOT_HANDLED;
    }

    CcspTraceDebug(("%s: %s\n", __FUNCTION__, eventName));
    if (interval)
    {
        if ((duration != 0) && (duration < interval))
        {
            CcspTraceError(("Invalid parameter, the duration should be greater than the interval.\n"));
            return RBUSCORE_ERROR_INVALID_PARAM;
        }
        if(added)
        {
            Ccsp_RbusInterval_Subscribe(userData, listener, eventName, componentId, interval, duration, filter);
        }
        else
        {
            Ccsp_RbusInterval_Unsubscribe(userData, listener, eventName, componentId, interval, duration, filter);
        }
    }
    else
    {
        if(added)
        {
            Ccsp_RbusValueChange_Subscribe(userData, listener, paramName, eventName, componentId, interval, duration, filter);
        }
        else
        {
            Ccsp_RbusValueChange_Unsubscribe(userData, listener, paramName, eventName, componentId, filter);
        }
    }

    return RBUSCORE_SUCCESS;
}

