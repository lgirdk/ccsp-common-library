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

    module:	slap_lco_interface.c

        For Service Logic Aggregation Plane Implementation (SLAP),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This module implements the some platform-dependent and
        general utility functions for Slap Loam Client Object.

        *   SlapCreateLoamClient

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        08/30/03    initial revision.

**********************************************************************/


#include "slap_lco_global.h"


/**********************************************************************

    caller:     component objects

    prototype:

        ANSC_HANDLE
        SlapCreateLoamClient
            (
                ANSC_HANDLE                 hContainerContext,
                ANSC_HANDLE                 hOwnerContext,
                ANSC_HANDLE                 hAnscReserved
            )

    description:

        This function is called to create a new Slap Loam Client
        object.

    argument:   ANSC_HANDLE                 hContainerContext
                This context handle is transparent to the object mapper
                wrapper, it's only meanful to the caller.

                ANSC_HANDLE                 hOwnerContext
                This context handle is transparent to the object mapper
                wrapper, it's only meanful to the caller.

                ANSC_HANDLE                 hAnscReserved
                This context handle is transparent to the object mapper
                wrapper, it's only meanful to the caller.

    return:     handle of the loam client object.

**********************************************************************/

ANSC_HANDLE
SlapCreateLoamClient
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    ANSC_STATUS                     returnStatus    = ANSC_STATUS_SUCCESS;
    PSLAP_LOAM_CLIENT_OBJECT        pSlapLoamClient = NULL;

    return  SlapLcoCreate(hContainerContext, hOwnerContext, hAnscReserved);
}
