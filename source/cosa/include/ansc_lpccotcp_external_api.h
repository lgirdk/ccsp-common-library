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

    module:	ansc_lpccotcp_external_api.h

        For Advanced Networking Service Container (ANSC),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the external functions provided by the Lpcco Tcp.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        08/23/03    initial revision.

**********************************************************************/


#ifndef  _ANSC_LPCCOTCP_EXTERNAL_API_
#define  _ANSC_LPCCOTCP_EXTERNAL_API_


/***********************************************************
     FUNCTIONS IMPLEMENTED IN ANSC_LPCCOTCP_INTERFACE.C
***********************************************************/

ANSC_HANDLE
AnscCreateLpccoTcp
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN ANSC_LPCCOTCP_BASE.C
***********************************************************/

ANSC_HANDLE
AnscLpccoTcpCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

ANSC_STATUS
AnscLpccoTcpRemove
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
AnscLpccoTcpEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
AnscLpccoTcpInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
