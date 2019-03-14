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

    module:	tls_aco_exported_api.h

        For Transport Layer Security Implementation (TLS),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by the TLS App Connector
        Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        05/26/03    initial revision.

**********************************************************************/


#ifndef  _TLS_ACO_EXPORTED_API_
#define  _TLS_ACO_EXPORTED_API_


/***********************************************************
        FUNCTIONS IMPLEMENTED IN TLS_ACO_INTERFACE.C
***********************************************************/

ANSC_HANDLE
TlsCreateAppConnector
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
           FUNCTIONS IMPLEMENTED IN TLS_ACO_BASE.C
***********************************************************/

ANSC_HANDLE
TlsAcoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

ANSC_STATUS
TlsAcoRemove
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
TlsAcoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
TlsAcoInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
