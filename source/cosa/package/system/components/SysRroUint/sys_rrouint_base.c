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

    module:	sys_rrouint_base.c

        For BroadWay Runtime System Environment (SYS),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This module implements the basic container object functions
        of the Sys Rro Uint Object.

        *   SysRroUintCreate
        *   SysRroUintRemove
        *   SysRroUintEnrollObjects
        *   SysRroUintInitialize

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        05/07/02    initial revision.

**********************************************************************/


#include "sys_rrouint_global.h"


/**********************************************************************

    caller:     owner of the object

    prototype:

        ANSC_HANDLE
        SysRroUintCreate
            (
                ANSC_HANDLE                 hContainerContext,
                ANSC_HANDLE                 hOwnerContext,
                ANSC_HANDLE                 hAnscReserved
            );

    description:

        This function constructs the Sys Rro Uint Object and
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
SysRroUintCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_LIGHT_COMPONENT_OBJECT    pBaseObject  = NULL;
    PSYS_RRO_UINT_OBJECT            pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PSYS_RRO_UINT_OBJECT)AnscAllocateMemory(sizeof(SYS_RRO_UINT_OBJECT));

    if ( !pMyObject )
    {
        return  (ANSC_HANDLE)NULL;
    }
    else
    {
        pBaseObject = (PANSC_LIGHT_COMPONENT_OBJECT)pMyObject;
    }

    /*
     * Initialize the common variables and functions for a container object.
     */
    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = SYS_RRO_UINT_OID;
    pBaseObject->Create            = SysRroUintCreate;
    pBaseObject->Remove            = SysRroUintRemove;
    pBaseObject->EnrollObjects     = SysRroUintEnrollObjects;
    pBaseObject->Initialize        = SysRroUintInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        SysRroUintRemove
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
SysRroUintRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSYS_RRO_UINT_OBJECT            pMyObject    = (PSYS_RRO_UINT_OBJECT)hThisObject;

    SysRroRemove((ANSC_HANDLE)pMyObject);

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        SysRroUintEnrollObjects
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
SysRroUintEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSYS_RRO_UINT_OBJECT            pMyObject    = (PSYS_RRO_UINT_OBJECT)hThisObject;

    SysRroEnrollObjects((ANSC_HANDLE)pMyObject);

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        SysRroUintInitialize
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
SysRroUintInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSYS_RRO_UINT_OBJECT            pMyObject    = (PSYS_RRO_UINT_OBJECT)hThisObject;

    /*
     * Until you have to simulate C++ object-oriented programming style with standard C, you don't
     * appreciate all the nice little things come with C++ language and all the dirty works that
     * have been done by the C++ compilers. Member initialization is one of these things. While in
     * C++ you don't have to initialize all the member fields inherited from the base class since
     * the compiler will do it for you, such is not the case with C.
     */
    SysRroInitialize((ANSC_HANDLE)pMyObject);

    /*
     * Although we have initialized some of the member fields in the "create" member function, we
     * repeat the work here for completeness. While this simulation approach is pretty stupid from
     * a C++/Java programmer perspective, it's the best we can get for universal embedded network
     * programming. Before we develop our own operating system (don't expect that to happen any
     * time soon), this is the way things gonna be.
     */
    pMyObject->Oid            = SYS_RRO_UINT_OID;
    pMyObject->Create         = SysRroUintCreate;
    pMyObject->Remove         = SysRroUintRemove;
    pMyObject->EnrollObjects  = SysRroUintEnrollObjects;
    pMyObject->Initialize     = SysRroUintInitialize;

    pMyObject->RecordType     = SYS_REP_RECORD_TYPE_UINT;
    pMyObject->RecordSize     = sizeof(ULONG);
    pMyObject->RecordValue    = 0;

    pMyObject->GetRecordData  = SysRroUintGetRecordData;
    pMyObject->SetRecordData  = SysRroUintSetRecordData;

    pMyObject->GetRecordValue = SysRroUintGetRecordValue;
    pMyObject->SetRecordValue = SysRroUintSetRecordValue;

    return  ANSC_STATUS_SUCCESS;
}
