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

    module:	kernel_time.h

        For Advanced Networking Service Container (ANSC),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco System  , Inc., 1997 ~ 2002
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This wrapper file defines some basic data types and
        structures on a particular platform.

    ---------------------------------------------------------------

    environment:

        OSE 4.2

    ---------------------------------------------------------------

    author:

        Hua Ding

    ---------------------------------------------------------------

    revision:

        07/31/02    initial revision.

**********************************************************************/


#ifndef  _KERNEL_TIME_
#define  _KERNEL_TIME_


/***********************************************************
        DEFINITION OF BASIC DATA TYPE AND STRUCTURES
***********************************************************/


/***********************************************************
       BASIC OPERATIONS BY MACROS AND INLINE FUNCTIONS
***********************************************************/

/*
void
KernelSleepInMilliSeconds
    (
        ULONG                       ulMilliSeconds
    );
 */
#define  KernelSleepInMilliSeconds(ms)              delay(ms)


/*
ULONG
KernelGetTickInSeconds
    (
        VOID
    );
 *
 *  1 system tick = 4 ms
 */
#define  KernelGetTickInSeconds()                   (get_ticks() / 250)


/*
ULONG
KernelGetTickInMillSeconds
    (
        VOID
    );
 */
#define  KernelGetTickInMilliSeconds()              (get_ticks() * 4)


/*
ULONG
KernelGetTickInMicroSeconds
    (
        VOID
    );
 */
#define  KernelGetTickInMicroSeconds()              (KernelGetTickInMilliSeconds() * 1000)


/*
void
KernelGetTickInMicroSeconds64
    (
        ULONG*                      hi_part,
        ULONG*                      lo_part
    );
 */
#define  KernelGetTickInMicroSeconds64(hi,lo)                   \
            {                                                   \
                *(hi) = 0;                                      \
                *(lo) = KernelGetTickInMicroSeconds();          \
            }


BOOL
KernelGetUniversalTime
    (
        KERNEL_HANDLE               hTime
    );


#endif
