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

    module:	http_atofxcat1_operation.c

        For HyperText Transfer Protocol Implementation (HTTP),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This module implements the advanced operation functions
        of the Http Ato FxCat1 Object.

        *   HttpAtoFxCat1CreateCodeTable
        *   HttpAtoFxCat1CreateNameTable
        *   HttpAtoFxCat1GetAtomCode
        *   HttpAtoFxCat1GetAtomName

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        03/20/02    initial revision.

**********************************************************************/


#include "http_atofxcat1_global.h"


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpAtoFxCat1CreateCodeTable
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function creates the atom table for HTTP CGI environment
        variables.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpAtoFxCat1CreateCodeTable
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PHTTP_ATO_FXCAT1_OBJECT         pMyObject    = (PHTTP_ATO_FXCAT1_OBJECT)hThisObject;
    ULONG                           i            = 0;

    while ( g_FileExtArray[i] )
    {
        pMyObject->AddAtomByName
            (
                (ANSC_HANDLE)pMyObject,
                g_FileExtArray  [i],
                g_MediaTypeArray[i],
                (ANSC_HANDLE)NULL
            );

        i++;
    }

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpAtoFxCat1CreateNameTable
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function creates the atom table for HTTP CGI environment
        variables.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpAtoFxCat1CreateNameTable
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

        ULONG
        HttpAtoFxCat1GetAtomCode
            (
                ANSC_HANDLE                 hThisObject,
                char*                       name
            );

    description:

        This function is called to retrieve the fxcat1 code for
        the corresponding fxcat1 name.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                char*                       name
                Specifies the fxcat1 name to be matched.

    return:     fxcat1 code.

**********************************************************************/

ULONG
HttpAtoFxCat1GetAtomCode
    (
        ANSC_HANDLE                 hThisObject,
        char*                       name
    )
{
    PHTTP_ATO_FXCAT1_OBJECT         pMyObject       = (PHTTP_ATO_FXCAT1_OBJECT)hThisObject;
    PANSC_ATOM_DESCRIPTOR           pAtomDescriptor = NULL;

    pAtomDescriptor =
        (PANSC_ATOM_DESCRIPTOR)pMyObject->GetAtomByName
            (
                (ANSC_HANDLE)pMyObject,
                name
            );

    if ( !pAtomDescriptor )
    {
        return  0;
    }

    return  pAtomDescriptor->AtomId;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        char*
        HttpAtoFxCat1GetAtomName
            (
                ANSC_HANDLE                 hThisObject,
                ULONG                       code
            );

    description:

        This function is called to retrieve the fxcat1 name for
        the corresponding fxcat1 code.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                ULONG                       code
                Specifies the fxcat1 code to be matched.

    return:     fxcat1 name.

**********************************************************************/

char*
HttpAtoFxCat1GetAtomName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       code
    )
{
    PHTTP_ATO_FXCAT1_OBJECT         pMyObject       = (PHTTP_ATO_FXCAT1_OBJECT)hThisObject;
    PANSC_ATOM_DESCRIPTOR           pAtomDescriptor = NULL;

    pAtomDescriptor =
        (PANSC_ATOM_DESCRIPTOR)pMyObject->GetAtomById
            (
                (ANSC_HANDLE)pMyObject,
                code
            );

    if ( !pAtomDescriptor )
    {
        return  NULL;
    }

    return  pAtomDescriptor->AtomName;
}
