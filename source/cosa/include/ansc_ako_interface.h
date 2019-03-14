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

    module:	ansc_ako_interface.h

        For Advanced Networking Service Container (ANSC),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for Ansc Access Key Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        05/18/02    initial revision.

**********************************************************************/


#ifndef  _ANSC_AKO_INTERFACE_
#define  _ANSC_AKO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_co_interface.h"
#include "ansc_co_external_api.h"
#include "ansc_ifo_interface.h"


/***********************************************************
      PLATFORM INDEPENDENT ACCESS KEY OBJECT DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the Atom Table Object definition.
 */
#define  ANSC_AKO_ACCESS_MODE_READ                  0x00000001
#define  ANSC_AKO_ACCESS_MODE_WRITE                 0x00000002
#define  ANSC_AKO_ACCESS_MODE_RDWR                  0x00000003

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */
typedef  ANSC_HANDLE
(*PFN_AKO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_STATUS
(*PFN_AKO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

typedef  ANSC_HANDLE
(*PFN_AKO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_STATUS
(*PFN_AKO_SET_IF)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );

typedef  ULONG
(*PFN_AKO_GET_MODE)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_STATUS
(*PFN_AKO_SET_MODE)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulMode
    );

typedef  ANSC_STATUS
(*PFN_AKO_RESET)
    (
        ANSC_HANDLE                 hThisObject
    );

/*
 * One of the most popular problems every developer has to face in multi-task programming is to
 * synchronize the access to shared resources. Normally, such mechanism should be implemented by
 * the target module/object that owns the resource. As an exception, we use a separate object
 * instead to manage the access to the Configuration Interface exposed by system modules. The
 * benefit of doing this is the clear isolation between the core technology developer and the
 * system developer/packager.
 */
#define  ANSC_ACCESS_KEY_CLASS_CONTENT                                                      \
    /* duplication of the base object class content */                                      \
    ANSCCO_CLASS_CONTENT                                                                    \
    /* start of object class content */                                                     \
    ANSC_HANDLE                     hOrgAccessIf;                                           \
    ANSC_HANDLE                     hCurAccessIf;                                           \
    ULONG                           AccessMode;                                             \
                                                                                            \
    PFN_AKO_GET_IF                  GetOrgAccessIf;                                         \
    PFN_AKO_SET_IF                  SetOrgAccessIf;                                         \
    PFN_AKO_GET_IF                  GetCurAccessIf;                                         \
    PFN_AKO_GET_MODE                GetAccessMode;                                          \
    PFN_AKO_SET_MODE                SetAccessMode;                                          \
    /* end of object class content */                                                       \

typedef  struct
_ANSC_ACCESS_KEY_OBJECT
{
    ANSC_ACCESS_KEY_CLASS_CONTENT
}
ANSC_ACCESS_KEY_OBJECT,  *PANSC_ACCESS_KEY_OBJECT;

#define  ACCESS_ANSC_ACCESS_KEY_OBJECT(p)           \
         ACCESS_CONTAINER(p, ANSC_ACCESS_KEY_OBJECT, Linkage)


#endif
