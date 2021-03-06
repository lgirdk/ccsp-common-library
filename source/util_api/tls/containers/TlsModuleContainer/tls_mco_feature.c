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

    module:	tls_mco_feature.c

        For Transport Layer Security Implementation (TLS),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This module implements the advanced operation functions
        of the Tls Module Container Object.

        *   TlsMcoEnrollFeatureObjects
        *   TlsMcoManufactureFeatureObjects
        *   TlsMcoDestroyFeatureObjects

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        09/13/03    initial revision.

**********************************************************************/


#include "tls_mco_global.h"


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsMcoEnrollFeatureObjects
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function is called to enroll all the internal objects.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsMcoEnrollFeatureObjects
    (
        ANSC_HANDLE                 hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsMcoManufactureFeatureObjects
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function is called to manufacture all the internal objects.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsMcoManufactureFeatureObjects
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PTLS_MODULE_CONTAINER_OBJECT    pMyObject         = (PTLS_MODULE_CONTAINER_OBJECT)hThisObject;
    PTLS_ENV_CONTROLLER_OBJECT      pTlsEnvController = (PTLS_ENV_CONTROLLER_OBJECT  )pMyObject->hTlsEnvController;

    if ( !pTlsEnvController )
    {
        pTlsEnvController =
            (PTLS_ENV_CONTROLLER_OBJECT)TlsCreateEnvController
                (
                    (ANSC_HANDLE)pMyObject,
                    (ANSC_HANDLE)pMyObject,
                    (ANSC_HANDLE)NULL
                );

        if ( !pTlsEnvController )
        {
            return  ANSC_STATUS_RESOURCES;
        }
        else
        {
            pMyObject->hTlsEnvController = (ANSC_HANDLE)pTlsEnvController;
        }
    }

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsMcoDestroyFeatureObjects
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function is called to destroy all the internal objects.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsMcoDestroyFeatureObjects
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PTLS_MODULE_CONTAINER_OBJECT    pMyObject         = (PTLS_MODULE_CONTAINER_OBJECT)hThisObject;
    PTLS_ENV_CONTROLLER_OBJECT      pTlsEnvController = (PTLS_ENV_CONTROLLER_OBJECT  )pMyObject->hTlsEnvController;

    if ( pTlsEnvController )
    {
        pTlsEnvController->Remove((ANSC_HANDLE)pTlsEnvController);

        pMyObject->hTlsEnvController = (ANSC_HANDLE)NULL;
    }

    return  ANSC_STATUS_SUCCESS;
}
