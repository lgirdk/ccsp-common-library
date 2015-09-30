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

    module:	tls_mco_base.c

        For Transport Layer Security Implementation (TLS),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2003
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This module implements the basic container object functions
        of the Tls Module Container Object.

        *   TlsMcoCreate
        *   TlsMcoRemove
        *   TlsMcoEnrollObjects
        *   TlsMcoInitialize

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

    caller:     owner of the object

    prototype:

        ANSC_HANDLE
        TlsMcoCreate
            (
                ANSC_HANDLE                 hContainerContext,
                ANSC_HANDLE                 hOwnerContext,
                ANSC_HANDLE                 hAnscReserved
            );

    description:

        This function constructs the Tls Module Container Object and
        initializes the member variables and functions.

    argument:   ANSC_HANDLE                 hContainerContext
                This handle is used by the container object to interact
                with the outside world. It could be the real container
                or an target object.

                ANSC_HANDLE                 hOwnerContext
                This handle is passed in by the owner of this object.

                ANSC_HANDLE                 hAnscReserved
                This handle is passed in by the owner of this object.

    return:     newly created container object.

**********************************************************************/

ANSC_HANDLE
TlsMcoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PTLS_MODULE_CONTAINER_OBJECT    pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PTLS_MODULE_CONTAINER_OBJECT)AnscAllocateMemory(sizeof(TLS_MODULE_CONTAINER_OBJECT));

    if ( !pMyObject )
    {
        return  (ANSC_HANDLE)NULL;
    }
    else
    {
        pBaseObject = (PANSC_COMPONENT_OBJECT)pMyObject;
    }

    /*
     * Initialize the common variables and functions for a container object.
     */
    /* AnscCopyString(pBaseObject->Name, TLS_MODULE_CONTAINER_NAME); */

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = TLS_MODULE_CONTAINER_OID;
    pBaseObject->Create            = TlsMcoCreate;
    pBaseObject->Remove            = TlsMcoRemove;
    pBaseObject->EnrollObjects     = TlsMcoEnrollObjects;
    pBaseObject->Initialize        = TlsMcoInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsMcoRemove
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function destroys the object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsMcoRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    AnscMcoRemove((ANSC_HANDLE)hThisObject);

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsMcoEnrollObjects
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function enrolls all the objects required by this object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsMcoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    )
{
    AnscMcoEnrollObjects((ANSC_HANDLE)hThisObject);

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsMcoInitialize
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function first calls the initialization member function
        of the base class object to set the common member fields
        inherited from the base class. It then initializes the member
        fields that are specific to this object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsMcoInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PTLS_MODULE_CONTAINER_OBJECT    pMyObject     = (PTLS_MODULE_CONTAINER_OBJECT)hThisObject;

    /*
     * Until you have to simulate C++ object-oriented programming style with standard C, you don't
     * appreciate all the nice little things come with C++ language and all the dirty works that
     * have been done by the C++ compilers. Member initialization is one of these things. While in
     * C++ you don't have to initialize all the member fields inherited from the base class since
     * the compiler will do it for you, such is not the case with C.
     */
    AnscMcoInitialize((ANSC_HANDLE)pMyObject);

    /*
     * Although we have initialized some of the member fields in the "create" member function, we
     * repeat the work here for completeness. While this simulation approach is pretty stupid from
     * a C++/Java programmer perspective, it's the best we can get for universal embedded network
     * programming. Before we develop our own operating system (don't expect that to happen any
     * time soon), this is the way things gonna be.
     */
    pMyObject->Oid                         = TLS_MODULE_CONTAINER_OID;
    pMyObject->Create                      = TlsMcoCreate;
    pMyObject->Remove                      = TlsMcoRemove;
    pMyObject->EnrollObjects               = TlsMcoEnrollObjects;
    pMyObject->Initialize                  = TlsMcoInitialize;

    pMyObject->EnrollExtensionObjects      = TlsMcoEnrollExtensionObjects;
    pMyObject->ManufactureExtensionObjects = TlsMcoManufactureExtensionObjects;
    pMyObject->DestroyExtensionObjects     = TlsMcoDestroyExtensionObjects;

    pMyObject->EnrollFeatureObjects        = TlsMcoEnrollFeatureObjects;
    pMyObject->ManufactureFeatureObjects   = TlsMcoManufactureFeatureObjects;
    pMyObject->DestroyFeatureObjects       = TlsMcoDestroyFeatureObjects;

    pMyObject->Ignite                      = TlsMcoIgnite;
    pMyObject->PutOut                      = TlsMcoPutOut;
    pMyObject->Switch                      = TlsMcoSwitch;

    pMyObject->RegisterIfs                 = TlsMcoRegisterIfs;
    pMyObject->DispatchIfs                 = TlsMcoDispatchIfs;

    pMyObject->hTlsEnvController           = (ANSC_HANDLE)NULL;

    pMyObject->GetTlsEnvController         = TlsMcoGetTlsEnvController;

    return  ANSC_STATUS_SUCCESS;
}
