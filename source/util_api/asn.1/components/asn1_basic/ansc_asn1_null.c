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

    module: ansc_asn1_null.c

        For ASN.1 NULL object

    ---------------------------------------------------------------

    description:

        This file implements the all the functions
        provided by the ASN.1 base class "ASN1_NULL"

        *   AnscAsn1NULLCreate
        *   AnscAsn1NULLInitialize
        *   AnscAsn1NULLClone
        *   AnscAsn1NULLCopyTo
        *   AnscAsn1NULLEqualsTo
        *   AnscAsn1NULLGetSizeOfEncoded
        *   AnscAsn1NULLDecodingData
        *   AnscAsn1NULLEncodingData
        *   AnscAsn1NULLDumpObject
        *   AnscAsn1NULLTraceObject

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Bin Zhu

    ---------------------------------------------------------------

    revision:

        03/17/02    initial revision.

**********************************************************************/

#include "ansc_asn1_local.h"

/**********************************************************************

    caller:     owner of the object

    prototype:

        ANSC_HANDLE
        AnscAsn1NULLCreate
            (
                ANSC_HANDLE                 hContainerContext
            );

    description:

        This function constructs an ASN.1 object and
        initializes the member variables and functions.

    argument:   ANSC_HANDLE                 hContainerContext
                This handle is used by the container object to interact
                with the outside world. It could be the real container
                or an target object.

    return:     newly created container object.

**********************************************************************/

ANSC_HANDLE
AnscAsn1NULLCreate
    (
        ANSC_HANDLE                 hContainerContext
    )
{
    PANSC_ASN1_NULL                 pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    if( hContainerContext != NULL)
    {
        pMyObject = (PANSC_ASN1_NULL)AnscAllocateMemory((ULONG)hContainerContext);
    }
    else
    {
        pMyObject = (PANSC_ASN1_NULL)AnscAllocateMemory(sizeof(ANSC_ASN1_NULL));
    }

    if ( !pMyObject )
    {
        return  (ANSC_HANDLE)NULL;
    }

    /*
     *  reset the SAttrList;
     */
    AnscSListInitializeHeader(&pMyObject->sAttrList);

    pMyObject->hContainerContext   = hContainerContext;
    pMyObject->hOwnerContext       = NULL;
    pMyObject->Oid                 = ANSC_ASN1_NULL_ID;
    pMyObject->uType               = ASN1_NULL_TYPE;
    pMyObject->bOptional           = FALSE;
    pMyObject->bCanBeOptional      = FALSE;
    pMyObject->Create              = AnscAsn1NULLCreate;
    pMyObject->AsnFree             = AnscAsn1Free;
    
    AnscAsn1NULLInitialize(pMyObject);

    /*
     * Initialize the common variables and functions for a container object.
     */
    pMyObject->SetName(pMyObject,ANSC_ASN1_NULL_NAME);
    pMyObject->SetClassName(pMyObject,ANSC_ASN1_NULL_CLASS_NAME);

    return  (ANSC_HANDLE)pMyObject;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        AnscAsn1NULLInitialize
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
AnscAsn1NULLInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_NULL                 pMyObject    = (PANSC_ASN1_NULL)hThisObject;

    /*
     *  Call base initialization first
     */
    AnscAsn1Initialize((ANSC_HANDLE)pMyObject);

    /* set other functions */
    pMyObject->Clone                = AnscAsn1NULLClone;
    pMyObject->CopyTo               = AnscAsn1NULLCopyTo;
    pMyObject->EqualsTo             = AnscAsn1NULLEqualsTo;
    pMyObject->DecodingData         = AnscAsn1NULLDecodingData;
    pMyObject->EncodingData         = AnscAsn1NULLEncodingData;
    pMyObject->GetSizeOfEncoded     = AnscAsn1NULLGetSizeOfEncoded;
    pMyObject->DumpObject           = AnscAsn1NULLDumpObject;

    return ANSC_STATUS_SUCCESS;
}

/**********************************************************************

    caller:     owner of the object

    prototype:

        ANSC_HANDLE
        AnscAsn1NULLClone
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function clones a same ASN.1 object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     The cloned container object.

**********************************************************************/
ANSC_HANDLE
AnscAsn1NULLClone
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_NULL                 pMyObject    = (PANSC_ASN1_NULL)hThisObject;
    PANSC_ASN1_NULL                 pNewObject   = NULL;

    pNewObject = (PANSC_ASN1_NULL)
                 pMyObject->Create
                    (
                        pMyObject->hContainerContext
                    );

    if( pNewObject == NULL)
    {
        AnscTrace("Failed to clone at AnscAsn1NULLClone()\n");

        return NULL;
    }

    /*
     *  Copy all the attributes;
     */
    /* AttrListCopyAllAttributes( &pNewObject->sAttrList, &pMyObject->sAttrList);*/
    pNewObject->SetName(pNewObject, pMyObject->Name);

    pMyObject->CopyTo(pMyObject, pNewObject);

    return pNewObject;
}


/**********************************************************************

    caller:     owner of the object

    prototype:

        BOOLEAN
        AnscAsn1NULLCopyTo
            (
                ANSC_HANDLE                 hThisObject,
                ANSC_HANDLE                 hDestObject
            );

    description:

        This function copies the value to the other one.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                ANSC_HANDLE                 hDestObject
                The dest object;

    return:     succeeded or not;

**********************************************************************/
BOOLEAN
AnscAsn1NULLCopyTo
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDestObject
    )
{
    PANSC_ASN1_NULL                 pMyObject    = (PANSC_ASN1_NULL)hThisObject;
    PANSC_ASN1_NULL                 pNewObject   = (PANSC_ASN1_NULL)hDestObject;

    if( pNewObject == NULL || pMyObject == NULL)
    {
        return FALSE;
    }
  
    /*
     *  Copy other values;
     */
    pNewObject->bOptional       = pMyObject->bOptional;
    pNewObject->bCanBeOptional  = pMyObject->bCanBeOptional;

    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOLEAN
        AnscAsn1NULLEqualsTo
            (
                ANSC_HANDLE                 hThisObject,
                ANSC_HANDLE                 hOtherObject,
                BOOLEAN                     bValueOnly
            );

    description:

        This function compares the value of the 2 ASN.1 objects.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                ANSC_HANDLE                 hOtherObject
                This handle is the other object will be compared to;

                BOOLEAN                     bValueOnly
                Check the value only or not;

    return:     If they have the same type and value, return TRUE;
                otherwise return FALSE.

**********************************************************************/
BOOLEAN
AnscAsn1NULLEqualsTo
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hOtherObject,
        BOOLEAN                     bValueOnly
    )
{
    PANSC_ASN1_NULL                 pMyObject  = (PANSC_ASN1_NULL)hThisObject;
    PANSC_ASN1_NULL                 pNewObject = (PANSC_ASN1_NULL)hOtherObject;

    /* check the pointer first */
    if( hThisObject == hOtherObject)
    {
        return TRUE;
    }

    if( hThisObject == NULL || hOtherObject == NULL)
    {
        AnscTrace("One of the parameter in AnscAsn1NULLEqualsTo() is NULL pointer.\n");

        return FALSE;
    }

    /* check the type */
    if( pMyObject->uType != pNewObject->uType)
    {
        AnscTrace("Different type in AnscAsn1NULLEqualsTo().\n");

        return FALSE;
    }

    /* check the attribute list */
    if( !bValueOnly)
    {
        if(!AttrListCompareAttributeList(&pMyObject->sAttrList, &pNewObject->sAttrList))
        {
            return FALSE;
        }
    }

    /* check the optional state */
    if( pMyObject->bOptional != pNewObject->bOptional)
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG
        AnscAsn1NULLGetSizeOfEncoded
            (
                ANSC_HANDLE                 hThisObject
            )

    description:

        This function returns the encoding size of the 
        ASN.1 object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     The encoding size of the ASN.1 object.
                If the object is not ready-to-encode, -1 will be 
                returned.

**********************************************************************/
LONG
AnscAsn1NULLGetSizeOfEncoded
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_NULL                 pMyObject    = (PANSC_ASN1_NULL)hThisObject;
    ULONG                           ulSize       = 0;
    ULONG                           i            = 0;

    /*
     * If it's optional, don't need encode
     */
    if( pMyObject->bOptional)
    {
        return 0;
    }

    if( !pMyObject->ReadyToEncode(pMyObject))
    {
        AnscTrace("The value of the NULL object is not ready to encode.\n");

        return -1;
    }

    ulSize              = 0;

    /*
     *  check the attribute list, from the end of the list;
     *  the tag length value is 1.
     */ 
    return AttrListGetSizeOfEncoded(&pMyObject->sAttrList, ulSize, 1);
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        AnscAsn1NULLDecodingData
            (
                ANSC_HANDLE                 hThisObject,
                PVOID*                      ppEncoding
            );

    description:

        This function is decoding data for ASN.1 object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PVOID*                      ppEncoding
                The pointer of the input binary data

    return:     status of decoding operation

**********************************************************************/
ANSC_STATUS
AnscAsn1NULLDecodingData
    (
        ANSC_HANDLE                 hThisObject,
        PVOID*                      ppEncoding
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_ASN1_NULL                 pMyObject    = (PANSC_ASN1_NULL)hThisObject;
    PANSC_TAGINFO_OBJECT            pTagInfo     = NULL;
    BOOLEAN                         bTagIncluded = TRUE;
    ULONG                           uLeftSize,uInfiniteTags;
    PUCHAR                          pEndBuffer   = NULL;

    /*
     * pointer to the start of unexamined raw encoding data
     */
    PUCHAR                          pEncodingUnit;

    /* check the parameters */
    if( hThisObject == NULL  || ppEncoding == NULL)
    {
        return ANSC_ASN1_BAD_PARAMETER;
    }

    /*
     *  check before decoding;
     */
    if( pMyObject->BeforeDecoding != NULL)
    {
        returnStatus = pMyObject->BeforeDecoding(pMyObject, ppEncoding);

        if( ANSC_STATUS_SUCCESS != returnStatus)
        {
            return returnStatus;
        }
    }

    /* parsing the data */
    pEncodingUnit   = (PUCHAR)*ppEncoding;

    /*
     * Decode the attrlist first;
     */
    returnStatus = 
        AttrListDecodingData
            (
                &pMyObject->sAttrList,
                (PVOID*)&pEncodingUnit,
                pMyObject->IsConstructive(pMyObject),
                &bTagIncluded,
                &uLeftSize,
                &uInfiniteTags
            );
    
    if( ANSC_STATUS_SUCCESS != returnStatus)
    {
        return returnStatus;
    }

    if( bTagIncluded)
    {
        pTagInfo        = (PANSC_TAGINFO_OBJECT)AnscTagInfoCreate();

        if( pTagInfo == NULL)
        {
            return ANSC_STATUS_RESOURCES;
        }

        /* parsing the data */
        pEncodingUnit   = (PUCHAR)*ppEncoding;
        returnStatus    = pTagInfo->ParsingData((ANSC_HANDLE)pTagInfo, pEncodingUnit);
        
        if( returnStatus != ANSC_STATUS_SUCCESS)
        {
            pTagInfo->Remove((ANSC_HANDLE)pTagInfo);

            return returnStatus;
        }

        /* check the tag matched or not */
        if( pTagInfo->FirstOctetOfTag
                != pMyObject->GetFirstOctet((ANSC_HANDLE)pMyObject))
        {
            /*
            AnscTrace
                (
                    "Unexpected tag in ASN1_NULL - '0x%.2X', expected - '0x%.2X'\n",
                    pTagInfo->FirstOctetOfTag,
                    pMyObject->GetFirstOctet((ANSC_HANDLE)pMyObject)
                );
            */
            pTagInfo->Remove((ANSC_HANDLE)pTagInfo);

            return ANSC_ASN1_UNEXPECTED_TAG;
        }

        if( pTagInfo->ulContentLength != 0 ||
            pTagInfo->GetSizeOfTag(pTagInfo)     != 1
          )
        {           
            pTagInfo->Remove((ANSC_HANDLE)pTagInfo);
            AnscTrace("The length of NULL tag or value is unacceptable.\n");

            return ANSC_ASN1_UNACCEPTABLE_VALUE_SIZE;
        }

         /* check the tag */
        if( pTagInfo->bIsInfinite)
        {
            AnscTrace("Infinite form is unacceptable for NULL object.\n");
            pTagInfo->Remove((ANSC_HANDLE)pTagInfo);

            return ANSC_ASN1_INVALID_ENCODE_LENGTH;
        }

        pEncodingUnit   += 1 + pTagInfo->GetSizeOfLength(pTagInfo);
        uLeftSize        = pTagInfo->ulContentLength;

        pTagInfo->Remove((ANSC_HANDLE)pTagInfo);
    }

    if( uInfiniteTags > 0)
    {
        AnscTrace("Infinite form is unacceptable for NULL object.\n");

        return ANSC_ASN1_INVALID_ENCODE_LENGTH;
    }

    if( uLeftSize != 0)
    {
        AnscTrace("The length of NULL tag must be 0, not '%d'\n", uLeftSize);

        return ANSC_ASN1_UNACCEPTABLE_VALUE_SIZE;
    }

    /*
     *  check after decoding;
     */
    if( pMyObject->AfterDecoding != NULL)
    {
        returnStatus = pMyObject->AfterDecoding(pMyObject, (PVOID*)&pEncodingUnit);

        if( ANSC_STATUS_SUCCESS != returnStatus)
        {
            return returnStatus;
        }
    }

    *ppEncoding             = (PVOID)pEncodingUnit;
    pMyObject->bOptional    = FALSE;

    return returnStatus;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        AnscAsn1NULLEncodingData
            (
                ANSC_HANDLE                 hThisObject,
                PVOID*                      ppEncoding
            );

    description:

        This function is decoding data for ASN.1 object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PVOID*                      ppEncoding
                The pointer of the output binary data

    return:     status of encoding operation

**********************************************************************/
ANSC_STATUS
AnscAsn1NULLEncodingData
    (
        ANSC_HANDLE                 hThisObject,
        PVOID*                      ppEncoding
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_ASN1_NULL                 pMyObject    = (PANSC_ASN1_NULL)hThisObject;
    BOOLEAN                         bTagIncluded = TRUE;
    LONG                            uSizeOfEncoded;
    ULONG                           uLeftSize;

    /*
     * shortcut pointer to a char array
     */
    PUCHAR                          pCharData       = (PUCHAR)*ppEncoding;
    PUCHAR                          pBackData       = pCharData;

    /*
     * If it's optional, don't need encode
     */
    if( pMyObject->bOptional)
    {
        return ANSC_STATUS_SUCCESS;
    }

    /*
     *  check before encoding;
     */
    if( pMyObject->BeforeEncoding != NULL)
    {
        returnStatus = pMyObject->BeforeEncoding(pMyObject, ppEncoding);

        if( ANSC_STATUS_SUCCESS != returnStatus)
        {
            return returnStatus;
        }
    }

    uSizeOfEncoded = pMyObject->GetSizeOfEncoded(pMyObject);

    if( uSizeOfEncoded < 0)
    {
        return ANSC_ASN1_NOT_READY_TO_ENCODE;
    }

    /*
     * Encode all attrlist first; 
     */
    returnStatus = 
        AttrListEncodingData
            (
                &pMyObject->sAttrList,
                (PVOID*)&pCharData,
                (ULONG)uSizeOfEncoded,
                pMyObject->IsConstructive(pMyObject),
                &bTagIncluded,
                &uLeftSize
            );

    if( ANSC_STATUS_SUCCESS != returnStatus)
    {
        return returnStatus;
    }

    /*
     *  Encode the tag first;
     */
    if ( bTagIncluded)
    {
        *pCharData              = pMyObject->GetFirstOctet(pMyObject);
        pCharData++;

        *pCharData              = 0x00;
        pCharData++;
    }

    /*
     *  Set the buffer before exit;
     */
    if( ANSC_STATUS_SUCCESS == returnStatus)
    {
        if( pCharData - pBackData != uSizeOfEncoded)
        {
            /*
            AnscTrace
                (
                    "Warning in Encoding NULL, the size of encoding \
                    is expected to be %d, but it's %d.\n",
                    uSizeOfEncoded,
                    (pCharData - pBackData)
                );
            */
        }

        /*
         *  check after encoding;
         */
        if( pMyObject->AfterEncoding != NULL)
        {
            returnStatus = pMyObject->AfterEncoding(pMyObject, (PVOID*)&pCharData);

            if( ANSC_STATUS_SUCCESS != returnStatus)
            {
                return returnStatus;
            }
        }

        *ppEncoding  =  (PVOID)pCharData;
    }

    return returnStatus;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOLEAN
        AnscAsn1NULLDumpObject
            (
                ANSC_HANDLE                 hThisObject,
                PCHAR                       pBuffer,
                PULONG                      pLength,
                BOOLEAN                     bIsRoot,
                BOOLEAN                     bShowValue
            );

    description:

        This function dump out the values in a tree structure.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PCHAR                       pBuffer,
                The output buffer;

                PULONG                      pLength,
                The pointer of buffer size;

                BOOLEAN                     bIsRoot,
                The object is the root or not;

                BOOLEAN                     bShowValue
                Specifies showing the value or not;

    return:     status of operation.

**********************************************************************/
BOOLEAN
AnscAsn1NULLDumpObject
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pBuffer,
        PULONG                      pLength,
        BOOLEAN                     bIsRoot,
        BOOLEAN                     bShowValue
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PANSC_ASN1_NULL                 pMyObject    = (PANSC_ASN1_NULL)hThisObject;
    CHAR                            pAttrBuffer[512]= { 0 };
    ULONG                           attrLength      = 512;
    PCHAR                           pName;

    if( pBuffer == NULL || pLength == NULL)
    {
        return FALSE;
    }

    AttrListDump( &pMyObject->sAttrList, pAttrBuffer, &attrLength);

    if( bIsRoot )
    {
        pName   = pMyObject->ClassName;
    }
    else
    {
        pName   = pMyObject->Name;
    }

    if( pName == NULL)
    {
        return FALSE;
    }

    if( pMyObject->bOptional)
    {
        *pLength = 
            AnscSprintfString
                (
                    pBuffer,
                    "%s ::=%s %s (Optional)",
                    pName,
                    pAttrBuffer,
                    ASN1Type2String(pMyObject->uType)
                );
    }
    else
    {
        *pLength = 
            AnscSprintfString
                (
                    pBuffer,
                    "%s ::=%s %s",
                    pName,
                    pAttrBuffer,
                    ASN1Type2String(pMyObject->uType)
                );
    }

    return  TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOLEAN
        AnscAsn1NULLTraceObject
            (
                ANSC_HANDLE                 hThisObject,
                LONG                        layer,
                BOOLEAN                     bShowValue,
                BOOLEAN                     bRecursive
            );

    description:

        This function dump out the values in a tree structure.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                LONG                        layer,
                Specifies the layer of current object.

                BOOLEAN                     bShowValue
                Specifies showing the value or not;

                BOOLEAN                     bRecursive
                Trace recursive or not;

    return:     status of operation.

**********************************************************************/
BOOLEAN
AnscAsn1NULLTraceObject
    (
        ANSC_HANDLE                 hThisObject,
        LONG                        layer,
        BOOLEAN                     bShowValue,
        BOOLEAN                     bRecursive
    )
{

    ANSC_STATUS                     returnStatus     = ANSC_STATUS_SUCCESS;
    PANSC_ASN1_NULL                 pMyObject        = (PANSC_ASN1_NULL)hThisObject;
    CHAR                            pAttrBuffer[512] = { 0 };
    ULONG                           attrLength       = 512;
    PCHAR                           pName;

    TraceTabs(layer);
    AttrListDump( &pMyObject->sAttrList, pAttrBuffer, &attrLength);

    if( layer  == 0)
    {
        pName   = pMyObject->ClassName;
    }
    else
    {
        pName   = pMyObject->Name;
    }

    if( pName == NULL)
    {
        return FALSE;
    }

    if( pMyObject->bOptional)
    {
        AnscTrace
            (
                "%s ::=%s %s (Optional)\n", 
                pName,
                pAttrBuffer,
                ASN1Type2String(pMyObject->uType)
            );
    }
    else
    {
        AnscTrace
            (
                "%s ::=%s %s \n", 
                pName,
                pAttrBuffer,
                ASN1Type2String(pMyObject->uType)
            );
    }

    return  TRUE;
}


