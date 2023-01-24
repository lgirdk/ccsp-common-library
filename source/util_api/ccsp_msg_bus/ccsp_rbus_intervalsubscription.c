/*
 * If not stated otherwise in this file or this component's Licenses.txt file
 * the following copyright and licenses apply:
 *
 * Copyright 2019 RDK Management
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
#define _GNU_SOURCE 1 //needed for pthread_mutexattr_settype
#include "ccsp_rbus_value_change.h"
#include "rbus_message_bus.h"
#include "ccsp_base_api.h"
#include "ccsp_message_bus.h"
#include "ccsp_trace.h"
#include <rtmessage/rtVector.h>
#include <rtmessage/rtTime.h>
#include <rbus/rbus.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <pthread.h>
#include <unistd.h>

#define ERROR_CHECK(CMD) \
{ \
  int err; \
  if((err=CMD) != 0) \
  { \
    CcspTraceError("Error %d:%s running command \n" #CMD, err, strerror(err)); \
  } \
}

static rtVector gRecord = NULL;
static pthread_mutex_t gMutex = PTHREAD_MUTEX_INITIALIZER;


typedef struct sRecord
{
    int running;
    pthread_mutex_t  mutex;
    pthread_t        thread;
    pthread_cond_t   cond;
    void* handle;
    char* listener;
    char* parameter;
    int32_t componentId;
    rbusFilter_t filter;
    int32_t interval;
    int32_t duration;
    char* value;
} sRecord;

void rbusFilter_AppendToMessage(rbusFilter_t filter, rbusMessage msg);/*from librbus.so*/
static void init_thread(sRecord* rec)
{
    pthread_mutexattr_t attrib;
    pthread_condattr_t cattrib;

    rec->running = 0;

    pthread_mutexattr_init(&attrib);
    pthread_mutexattr_settype(&attrib, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&rec->mutex, &attrib);

    pthread_condattr_init(&cattrib);
    pthread_condattr_setclock(&cattrib, CLOCK_MONOTONIC);
    pthread_cond_init(&rec->cond, &cattrib);
    pthread_condattr_destroy(&cattrib);
}

static void sub_Free(void* p)
{
    sRecord* rec = (sRecord*)p;
    if(rec)
    {
        pthread_mutex_destroy(&rec->mutex);
        pthread_cond_destroy(&rec->cond);
        if(rec->listener)
            free(rec->listener);
        if(rec->parameter)
            free(rec->parameter);
        if(rec->value)
            free(rec->value);
        if(rec->filter)
            rbusFilter_Release(rec->filter);
        free(rec);
    }
}

static sRecord* sub_Find(void* handle, const char* listener,
        const char* parameter, int32_t componentId,
        rbusFilter_t filter, int32_t interval,
        int32_t duration)
{
    size_t i;
    for(i=0; i < rtVector_Size(gRecord); ++i)
    {
        sRecord* rec = (sRecord*)rtVector_At(gRecord, i);
        if( rec && rec->handle == handle &&
                strcmp(rec->listener, listener) == 0 &&
                strcmp(rec->parameter, parameter) == 0 &&
                rec->componentId == componentId &&
                rbusFilter_Compare(rec->filter, filter) == 0 &&
                rec->interval == interval && rec->duration == duration)
        {
            return rec;
        }
    }
    return NULL;
}

static parameterValStruct_t** rbusValueChange_GetParameterValue(sRecord* rec)
{
    int rc;
    int num_values;
    parameterValStruct_t **values = 0;
    CCSPBASEIF_GETPARAMETERVALUES getParameterValues =
        ((CCSP_Base_Func_CB* )(((CCSP_MESSAGE_BUS_INFO*)rec->handle)->CcspBaseIf_func))->getParameterValues;

    void* getParameterValues_data =
        ((CCSP_Base_Func_CB* )(((CCSP_MESSAGE_BUS_INFO*)rec->handle)->CcspBaseIf_func))->getParameterValues_data;

    rc = getParameterValues(0, &rec->parameter, 1, &num_values, &values, getParameterValues_data);
    if(rc == CCSP_SUCCESS)
    {
        if(num_values == 1)
        {
            CcspTraceDebug(("%s %s success %s\n", __FUNCTION__, rec->parameter, values[0]->parameterValue));
            return values;
        }
        else
        {
            CcspTraceWarning(("%s %s unexpected num_vals %d\n", __FUNCTION__, rec->parameter, num_values));
        }
        free_parameterValStruct_t(rec->handle, num_values, values);
    }
    else
    {
        CcspTraceError(("%s %s failed %d\n", __FUNCTION__, rec->parameter, rc));
    }
    return NULL;
}

static void* rbusInterval_PublishingThreadFunc(void *rec)
{
    CcspTraceWarning(("%s: start\n", __FUNCTION__));
    struct sRecord *sub_rec = (struct sRecord*)rec;
    int count = 0;
    int duration_count = 0;
    bool duration_complete = false;
    pthread_mutex_lock(&sub_rec->mutex);
    while(sub_rec->running)
    {
        parameterValStruct_t **val = NULL;
        int err;
        rtTime_t timeout;
        rtTimespec_t ts;
        rtTime_Later(NULL, (sub_rec->interval*1000), &timeout);
        err = pthread_cond_timedwait(&sub_rec->cond,
                &sub_rec->mutex,
                rtTime_ToTimespec(&timeout, &ts));
        if(err != 0 && err != ETIMEDOUT)
        {
            CcspTraceError(("Error %d:%s running command pthread_cond_timedwait", err, strerror(err)));
        }

        val = rbusValueChange_GetParameterValue(sub_rec);
        if(val)
        {
            rbusMessage msg;
            rbusCoreError_t err;
            /*construct a message just like rbus would construct it*/
            rbusMessage_Init(&msg);
            rbusMessage_SetString(msg, sub_rec->parameter);/*event name*/

            if (sub_rec->duration != 0)
            {
                duration_count = sub_rec->duration/sub_rec->interval;
                if (count >= duration_count)
                    duration_complete = true;
            }

            if (duration_complete)
            {
                /* Update event type after duration timeout*/
                rbusMessage_SetInt32(msg, RBUS_EVENT_DURATION_COMPLETE);/*event type*/
            }
            else
            {
                rbusMessage_SetInt32(msg, RBUS_EVENT_INTERVAL);/*event type*/
            }
            rbusMessage_SetString(msg, NULL);/*object name*/
            rbusMessage_SetInt32(msg, RBUS_OBJECT_SINGLE_INSTANCE);/*object type*/
            rbusMessage_SetInt32(msg, 1);/*number properties*/
            //prop 1: value
            rbusMessage_SetString(msg, "value");
            rbusMessage_SetInt32(msg, val[0]->type);/*alternavitely we could use the true rbus type/value currently stored in newVal*/
            rbusMessage_SetString(msg, val[0]->parameterValue);
            rbusMessage_SetInt32(msg, 0);/*object child object count*/
            if(sub_rec->filter)
            {
                rbusMessage_SetInt32(msg, 1);
                rbusFilter_AppendToMessage(sub_rec->filter, msg);
            }
            else
            {
                rbusMessage_SetInt32(msg, 0);
            }
            rbusMessage_SetInt32(msg, sub_rec->interval);
            rbusMessage_SetInt32(msg, sub_rec->duration);
            rbusMessage_SetInt32(msg, sub_rec->componentId);

            CcspTraceDebug(("%s: publising event %s to listener %s componentId %d\n", __FUNCTION__,
                        sub_rec->parameter, sub_rec->listener, sub_rec->componentId));
            err = rbus_publishSubscriberEvent(
                    ((CCSP_MESSAGE_BUS_INFO*)sub_rec->handle)->component_id,
                    sub_rec->parameter,
                    sub_rec->listener,
                    msg);
            rbusMessage_Release(msg);
            if(err != RBUSCORE_SUCCESS)
            {
                CcspTraceError(("%s rbus_publishSubscriberEvent failed error %d\n", __FUNCTION__, err));
            }
            free(sub_rec->value);
            sub_rec->value = strdup(val[0]->parameterValue);
            free_parameterValStruct_t(sub_rec->handle, 1, val);
            /*Duration complete*/
            if (duration_complete)
            {
                break;
            }
            else
            {
                count++;
            }
        }
        else
        {
            CcspTraceWarning(("%s getParameterValues failed\n", __FUNCTION__));
        }
    }
    pthread_mutex_unlock(&sub_rec->mutex);
    /*Removing duraiton completed sub from gRecord*/ 
    if (duration_complete) 
    {
        pthread_mutex_lock(&gMutex);
        rtVector_RemoveItem(gRecord, sub_rec, sub_Free);
        pthread_mutex_unlock(&gMutex);
    }
    CcspTraceWarning(("%s: stop\n", __FUNCTION__));
    return NULL;
}

int Ccsp_RbusInterval_Subscribe(void* handle, const char* listener,
        const char* parameter,
        int32_t componentId,
        int32_t interval,
        int32_t duration,
        rbusFilter_t filter)
{
    sRecord* rec;
    CcspTraceDebug(("%s: %s\n", __FUNCTION__, parameter));

    /*verify bus handle is valid*/
    if( handle == NULL ||
            ((CCSP_MESSAGE_BUS_INFO*)handle)->CcspBaseIf_func == NULL ||
            ((CCSP_Base_Func_CB* )(((CCSP_MESSAGE_BUS_INFO*)handle)->CcspBaseIf_func))->getParameterValues == NULL)
    {
        CcspTraceError(("%s NULL bus info\n", __FUNCTION__));
        return CCSP_FAILURE;
    }

    if (!gRecord)
        rtVector_Create(&gRecord);

    pthread_mutex_lock(&gMutex);
    rec = sub_Find(handle, listener, parameter, componentId, filter, interval, duration);
    pthread_mutex_unlock(&gMutex);

    if(!rec)
    {
        parameterValStruct_t **val = NULL;
        rec = (sRecord*)malloc(sizeof(sRecord));
        init_thread(rec);
        rec->handle = handle;
        rec->listener = strdup(listener);
        rec->parameter = strdup(parameter);
        rec->componentId = componentId;
        rec->filter = filter;
        rec->interval = interval;
        rec->duration = duration;
        rec->value = NULL;
        if(rec->filter)
            rbusFilter_Retain(rec->filter);
        val = rbusValueChange_GetParameterValue(rec);
        if(val)
        {
            rec->value = strdup(val[0]->parameterValue);
            free_parameterValStruct_t(rec->handle, 1, val);
        }
        CcspTraceDebug(("%s: %s new subscriber from listener %s componentId %d\n", __FUNCTION__,
                    rec->parameter, rec->listener, rec->componentId));
        rec->running = 1;
        pthread_create(&rec->thread, NULL, rbusInterval_PublishingThreadFunc, rec);

        pthread_mutex_lock(&gMutex);
        rtVector_PushBack(gRecord, rec);
        pthread_mutex_unlock(&gMutex);
    }
    else
    {
        CcspTraceDebug(("%s: ignoring duplicate subscribe for %s from listener %s componentId %d\n",
                    __FUNCTION__, rec->parameter, rec->listener, rec->componentId));
    }
    if(filter)
    {
        rbusFilter_Release(filter);
    }
    return CCSP_SUCCESS;
}


int Ccsp_RbusInterval_Unsubscribe(void* handle, const char* listener,
        const char* parameter,
        int32_t componentId,
        int32_t interval,
        int32_t duration,
        rbusFilter_t filter)
{
    sRecord* rec = NULL;
    (void)(handle);
    CcspTraceDebug(("%s: %s\n", __FUNCTION__, parameter));
    if(!gRecord)
    {
        return CCSP_FAILURE;
    }

    pthread_mutex_lock(&gMutex);
    rec = sub_Find(handle, listener, parameter, componentId, filter, interval, duration);
    pthread_mutex_unlock(&gMutex);

    if(filter)
    {
        rbusFilter_Release(filter);
    }

    if(rec)
    {
        if(rec->running)
        {
            rec->running = 0;
            pthread_cond_signal(&rec->cond);
            pthread_join(rec->thread, NULL);
        }
        pthread_mutex_lock(&gMutex);
        rtVector_RemoveItem(gRecord, rec, sub_Free);
        pthread_mutex_unlock(&gMutex);
    }
    else
    {
        CcspTraceWarning(("%s: param not found: %s\n", __FUNCTION__, parameter));
        return CCSP_FAILURE;
    }
    return CCSP_SUCCESS;
}
