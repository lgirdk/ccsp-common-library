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

    MODULE: ansc_asn1_CertificateRequest.c

        ASN.1 ANSC Code Generated by Cisco Systems, Inc.

    ---------------------------------------------------------------

    DESCRIPTION:

        The ASN.1 objects implemented in this file

        *   ANSC_ASN1_CERTIFICATEREQUEST
        *   ANSC_ASN1_CERTIFICATIONREQUESTINFO


    ---------------------------------------------------------------

    ENVIRONMENT:

        platform independent

    ---------------------------------------------------------------

    AUTHOR:

        ASNMAGIC ANSC CODE GENERATOR 1.0

    ---------------------------------------------------------------

    REVISION HISTORY:

        *   04/30/2002  initial revision

 **********************************************************************/


#include "ansc_asn1_advanced_local.h"

#ifndef _PKI_KERNEL
/**********************************************************************

 OBJECT -- ANSC_ASN1_CERTIFICATEREQUEST

 CertificateRequest ::= Sequence 
     {
            certificateRequestInfo CertificationRequestInfo 
      signatureAlgorithmIdentifier SignatureAlgorithmIdentifier 
                         signature BitString 
     }

 **********************************************************************/
ANSC_HANDLE
AnscAsn1GenPKCS10RequestWithCryptoAPI
    (
        ANSC_HANDLE                 hReserved,
        PALCERTIFICATE_ATTRIBUTE    pAttrObject,
        ANSC_HANDLE                 hCryptAPI
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = NULL;
    PCRYPT_API_STRUCT               pCryptAPI    = (PCRYPT_API_STRUCT)hCryptAPI;

    if( pAttrObject == NULL || hCryptAPI == NULL)
    {
        return NULL;
    }

    if( pCryptAPI->pGetPublicKey == NULL || pCryptAPI->pSignData == NULL)
    {
        AnscTrace("Invalid Smartcard APIs.\n");
        return NULL;
    }

    pThisObject = 
        (PANSC_ASN1_CERTIFICATEREQUEST)
        AnscAsn1CreateCertificateRequest
            (
                hReserved
            );

    if( pThisObject == NULL)
    {
        return NULL;
    }

    pThisObject->InitName
        (
            pThisObject,
            pAttrObject
        );

    pThisObject->InitWithCryptAPI
        (
            pThisObject,
            hCryptAPI
        );

    return pThisObject;
}

ANSC_HANDLE
AnscAsn1GeneratePKCS10Request
    (
        ANSC_HANDLE                 hReserved,
        PALCERTIFICATE_ATTRIBUTE    pAttrObject,
        ANSC_HANDLE                 hKeyPairHandle
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = NULL;

    pThisObject = 
        (PANSC_ASN1_CERTIFICATEREQUEST)
        AnscAsn1CreateCertificateRequest
            (
                hReserved
            );

    if( pThisObject == NULL)
    {
        return NULL;
    }

    pThisObject->InitName
        (
            pThisObject,
            pAttrObject
        );

    pThisObject->InitKeyPair
        (
            pThisObject,
            pAttrObject->KeyType,
            hKeyPairHandle
        );

    return pThisObject;
}


ANSC_HANDLE 
AnscAsn1CreateCertificateRequest
    (
        ANSC_HANDLE                 hReserved
    )
{
    UNREFERENCED_PARAMETER(hReserved);
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = NULL;

    /*
     * Create the base ASN.1 object.
     */
    pThisObject = (PANSC_ASN1_CERTIFICATEREQUEST)
        AnscAsn1CreateSequence
            (
                (ANSC_HANDLE)sizeof(ANSC_ASN1_CERTIFICATEREQUEST)
            );

    if( pThisObject == NULL)
    {
        return (ANSC_HANDLE)NULL;
    }

    /*
     * Initialize the common variables and functions for this ASN.1 object.
     */
    pThisObject->SetClassName(pThisObject, "ANSC_ASN1_CERTIFICATEREQUEST");
    pThisObject->SetName(pThisObject, "CertificateRequest");

    pThisObject->Create             = AnscAsn1CreateCertificateRequest;
    pThisObject->AsnFree            = AnscAsn1CertificateRequestFree;
    pThisObject->CreateChildAttr    = AnscAsn1CertificateRequestCreateChildAttr;
    pThisObject->GetChildName       = AnscAsn1CertificateRequestGetChildName;
    pThisObject->CreateChildObject  = AnscAsn1CertificateRequestCreateChildObject;
    pThisObject->GetCertificateRequestInfo
                                    = AnscAsn1CertificateRequestGetCertificateRequestInfo;
    pThisObject->GetSignatureAlgorithmIdentifier
                                    = AnscAsn1CertificateRequestGetSignatureAlgorithmIdentifier;
    pThisObject->GetSignature       = AnscAsn1CertificateRequestGetSignature;

    pThisObject->GetSubjectHandle   = AnscAsn1PKCS10GetSubjectHandle;
    pThisObject->SetPublicKeyInfo   = AnscAsn1PKCS10SetPublicKeyInfo;
    pThisObject->SetSignatureAlg    = AnscAsn1PKCS10SetSignatureAlg;
    pThisObject->GetSignatureType   = AnscAsn1PKCS10GetSignatureType;
    pThisObject->BeforeDecodingChild 
                                    = AnscAsn1PKCS10BeforeDecodingChild;
    pThisObject->AfterDecodingChild = AnscAsn1PKCS10AfterDecodingChild;
    pThisObject->AfterDecoding      = AnscAsn1PKCS10AfterDecoding;
    pThisObject->Verify             = AnscAsn1PKCS10Verify;
    pThisObject->SignWithCryptAPI   = AnscAsn1PKCS10SignWithCryptAPI;
    pThisObject->SignWithPrivateKeyInfo
                                    = AnscAsn1PKCS10SignWithPrivateKeyInfo;
    pThisObject->SignWithKeyParam   = AnscAsn1PKCS10SignWithKeyParam;
    pThisObject->InitKeyPair        = AnscAsn1PKCS10InitKeyPair;
    pThisObject->InitWithCryptAPI   = AnscAsn1PKCS10InitWithCryptoAPI;
    pThisObject->InitName           = AnscAsn1PKCS10InitName;

    pThisObject->pSignedData        = NULL;
    pThisObject->uSignedLength      = 0;

    pThisObject->uTotalChild        = 3;

    /*
     * Create all the children
     */
    pThisObject->CreateAllChildren(pThisObject);

    return (ANSC_HANDLE)pThisObject;
}

ANSC_STATUS
AnscAsn1CertificateRequestFree
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pBaseObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_OBJECT               pChild       = NULL;

    if( pBaseObject != NULL)
    {
        /* free the signed data part */
        if( pBaseObject->pSignedData != NULL && pBaseObject->uSignedLength > 0)
        {
            AnscFreeMemory(pBaseObject->pSignedData);
        }

        /*
         *  Remove the children here, from the end;
         */
        pBaseObject->RemoveAllChildren(pBaseObject,TRUE);

        /*
         *  Remove the extra child;
         */
        pChild = pBaseObject->pExtraChild;

        if( pChild != NULL)
        {
            pChild->AsnFree(pChild);
        }

        if( pBaseObject->Name != NULL)
        {
            AnscFreeMemory(pBaseObject->Name);
        }

        if( pBaseObject->ClassName != NULL)
        {
            AnscFreeMemory(pBaseObject->ClassName);
        }

        AttrListRemoveAllAttributes(&pBaseObject->sAttrList);

        AnscFreeMemory(pBaseObject);
    }

    return  ANSC_STATUS_SUCCESS;
}


ANSC_HANDLE
AnscAsn1CertificateRequestCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    )
{
    PANSC_ASN1_OBJECT               pThisObject      = NULL;
    PANSC_ASN1_SEQUENCE             pParent          = (PANSC_ASN1_SEQUENCE)hThisObject;

    switch( index )
    {

        case 0:

            pThisObject = AnscAsn1CreateCertificationRequestInfo(NULL);

            if( pThisObject != NULL)
            {
                pThisObject->AddAttribute(pThisObject, pParent->CreateChildAttr(pParent,index), FALSE);
                pThisObject->SetName(pThisObject, pParent->GetChildName(pParent,index));
            }

            break;

        case 1:

            pThisObject = AnscAsn1CreateSignatureAlgorithmIdentifier(NULL);

            if( pThisObject != NULL)
            {
                pThisObject->AddAttribute(pThisObject, pParent->CreateChildAttr(pParent,index), FALSE);
                pThisObject->SetName(pThisObject, pParent->GetChildName(pParent,index));
            }

            break;

        case 2:

            pThisObject = AnscAsn1CreateBitString(NULL);

            if( pThisObject != NULL)
            {
                pThisObject->AddAttribute(pThisObject, pParent->CreateChildAttr(pParent,index), FALSE);
                pThisObject->SetName(pThisObject, pParent->GetChildName(pParent,index));
            }

            break;

    }

    return pThisObject;

}

PANSC_ATTR_OBJECT
AnscAsn1CertificateRequestCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    UNREFERENCED_PARAMETER(index);
    PANSC_ATTR_OBJECT               pAttrObject  = NULL;

    return pAttrObject;

}

PCHAR
AnscAsn1CertificateRequestGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    )
{

#ifndef _PKI_KERNEL
    UNREFERENCED_PARAMETER(hThisObject);
    switch ( index )
    {
        case 0:

            return"certificateRequestInfo";

        case 1:

            return"signatureAlgorithmIdentifier";

        case 2:

            return"signature";

    }

#endif

    return "";

}

ANSC_HANDLE
AnscAsn1CertificateRequestGetCertificateRequestInfo
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_SEQUENCE             pParent          = (PANSC_ASN1_SEQUENCE)hThisObject;

    return pParent->GetChildByIndex(pParent, 0);

}

ANSC_HANDLE
AnscAsn1CertificateRequestGetSignatureAlgorithmIdentifier
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_SEQUENCE             pParent          = (PANSC_ASN1_SEQUENCE)hThisObject;

    return pParent->GetChildByIndex(pParent, 1);

}

ANSC_HANDLE
AnscAsn1CertificateRequestGetSignature
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_SEQUENCE             pParent          = (PANSC_ASN1_SEQUENCE)hThisObject;

    return pParent->GetChildByIndex(pParent, 2);

}

/*
 *  Manually added functions;
 */
SIGNATURE_TYPE
AnscAsn1PKCS10GetSignatureType
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_SIGNATUREALGORITHMIDENTIFIER
                                    pSignature;
    CHAR                            pOIDString[128] = { 0 };

    if( pThisObject == NULL)
    {
        return SIGNATURE_RESERVED;
    }

    pSignature = (PANSC_ASN1_SIGNATUREALGORITHMIDENTIFIER)
        pThisObject->GetSignatureAlgorithmIdentifier(pThisObject);

    if( pSignature == NULL)
    {
        return SIGNATURE_RESERVED;
    }

    pSignature->GetAlgorOIDStringValue(pSignature, pOIDString);

    return PKIOIDStringToSignatureType(pOIDString);
}

BOOLEAN
AnscAsn1PKCS10SetSignatureAlg
    (
        ANSC_HANDLE                 hThisObject,
        SIGNATURE_TYPE              signType
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_SIGNATUREALGORITHMIDENTIFIER
                                    pSignature;
    if( pThisObject == NULL)
    {
        return FALSE;
    }

    pSignature = (PANSC_ASN1_SIGNATUREALGORITHMIDENTIFIER)
        pThisObject->GetSignatureAlgorithmIdentifier(pThisObject);

    if( pSignature != NULL)
    {
        pSignature->SetAlgorOIDStringValue(pSignature, PKISignTypeToOIDString(signType));
    }

    return TRUE;
}


BOOLEAN
AnscAsn1PKCS10SetPublicKeyInfo
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyHandle
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject     = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_OBJECT               pKeyObj         = (PANSC_ASN1_OBJECT)hKeyHandle;
    PANSC_ASN1_SUBJECTPUBLICKEYINFO pPublicKeyInfo;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO
                                    pInfo;

    if( hThisObject == NULL  || hKeyHandle == NULL)
    {
        return FALSE;
    }

    pInfo = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
            pThisObject->GetCertificateRequestInfo(pThisObject);

    if( pInfo == NULL)
    {
        return FALSE;
    }

    if( AnscEqualString1(pKeyObj->ClassName, "ANSC_ASN1_SUBJECTPUBLICKEYINFO",FALSE))
    {
        return (ANSC_STATUS_SUCCESS == 
                 pInfo->SetChildByIndex
                    (
                        pInfo,
                        hKeyHandle, 
                        2,
                        TRUE
                    )); 
    }
    else if( AnscEqualString1(pKeyObj->ClassName, "ANSC_ASN1_PUBLICKEY",FALSE))
    {
        hKeyHandle = ((PANSC_ASN1_CHOICE)pKeyObj)->hSelection;

        if( hKeyHandle == NULL ||
            AnscEqualString1
            (
                ((PANSC_ASN1_OBJECT)hKeyHandle)->ClassName,
                "ANSC_ASN1_DSAPUBLICKEY",
                FALSE
            )
          )
        {
            return FALSE;
        }
        /* RSA Key */
    }
    else if( !AnscEqualString1(pKeyObj->ClassName, "ANSC_ASN1_RSAPUBLICKEY",FALSE))
    {
        return FALSE;
    }

    /* else set the key  */
    pPublicKeyInfo = (PANSC_ASN1_SUBJECTPUBLICKEYINFO)pInfo->GetChildByIndex(pInfo,2);

    if( pPublicKeyInfo == NULL)
    {
        return FALSE;
    }

    return 
        pPublicKeyInfo->InitPublicKey
            (
                pPublicKeyInfo,
                PKI_RSA_KEY,
                pKeyObj,
                NULL
            );
}

ANSC_HANDLE
AnscAsn1PKCS10GetSubjectHandle
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO
                                    pInfo;

    if( pThisObject == NULL)
    {
        return NULL;
    }

    pInfo = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
            pThisObject->GetCertificateRequestInfo(pThisObject);

    if( pInfo == NULL)
    {
        return NULL;
    }

    return pInfo->GetChildByIndex(pInfo,1);
}

ANSC_STATUS
AnscAsn1PKCS10BeforeDecodingChild
    (
        ANSC_HANDLE                 hThisObject,
        int                         index,
        PVOID*                      ppEncoding
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;

    if( pThisObject != NULL && index == 0)
    {
        /* free the signed data part */
        if( pThisObject->pSignedData != NULL && pThisObject->uSignedLength > 0)
        {
            AnscFreeMemory(pThisObject->pSignedData);
        }

        pThisObject->pSignedData    = *ppEncoding;
        pThisObject->uSignedLength  = 0;
    }

    return ANSC_STATUS_SUCCESS;
}

ANSC_STATUS
AnscAsn1PKCS10AfterDecodingChild
    (
        ANSC_HANDLE                 hThisObject,
        int                         index,
        PVOID*                      ppEncoding
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PUCHAR                          pEndBuffer   = *ppEncoding;
    PUCHAR                          pBack;

    if( pThisObject != NULL && index == 0)
    {
        pThisObject->uSignedLength  = pEndBuffer - pThisObject->pSignedData;

        /* make a copy here */
        pBack = pThisObject->pSignedData;

        pThisObject->pSignedData
            = (PUCHAR)AnscAllocateMemory(pThisObject->uSignedLength + 8);

        if( pThisObject->pSignedData != NULL)
        {
            AnscCopyMemory
                (
                    pThisObject->pSignedData,
                    pBack,
                    pThisObject->uSignedLength
                );
        }
        else
        {
            pThisObject->uSignedLength = 0;
        }
    }

    return ANSC_STATUS_SUCCESS;

}

ANSC_STATUS
AnscAsn1PKCS10AfterDecoding
    (
        ANSC_HANDLE                 hThisObject,
        PVOID*                      ppEncoding
    )
{
    UNREFERENCED_PARAMETER(ppEncoding);
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;

    if( pThisObject == NULL)
    {
        return returnStatus;
    }

    if( !pThisObject->Verify(pThisObject))
    {
        AnscTrace("Failed to verify the PKCS10 request.\n");

        returnStatus = ANSC_ASN1_FAILED_TO_VERIFY;
    }
    else
    {
        AnscTrace("Verify the PKCS10 Request successsfully.\n");
    }

    return returnStatus;
}

BOOLEAN
AnscAsn1PKCS10Verify
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_BITSTRING            pBitString;
    PANSC_ASN1_SUBJECTPUBLICKEYINFO pPublicKeyInfo;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO
                                    pInfo;
    SIGNATURE_TYPE                  signType;
    PUCHAR                          pSignature;

    if( pThisObject == NULL)
    {
        return FALSE;
    }

    pInfo = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
            pThisObject->GetCertificateRequestInfo(pThisObject);

    if( pInfo == NULL)
    {
        return FALSE;
    }

    pPublicKeyInfo = (PANSC_ASN1_SUBJECTPUBLICKEYINFO)
        pInfo->GetChildByIndex(pInfo,2);

    if( pPublicKeyInfo == NULL)
    {
        return FALSE;
    }

    /* get the signed data */
    if( pThisObject->pSignedData == NULL || pThisObject->uSignedLength == 0)
    {
        pThisObject->pSignedData = 
            pInfo->GetEncodedData
                (
                    pInfo,
                    &pThisObject->uSignedLength
                );
    }

    if( pThisObject->pSignedData == NULL || pThisObject->uSignedLength == 0)
    {
        return FALSE;
    }

    /* Get the signature data */
    pBitString = (PANSC_ASN1_BITSTRING)pThisObject->GetSignature(pThisObject);
    
    if( pBitString->uLength <= 4)
    {
        AnscTrace("Invalid signature \n");
        return FALSE;
    }

    signType = pThisObject->GetSignatureType(pThisObject);

    if( pBitString->bIsDynamic)
    {
        pSignature = pBitString->pStringBuffer;
    }
    else
    {
        pSignature = pBitString->pString;
    }

    return ANSC_STATUS_SUCCESS == 
                pPublicKeyInfo->Verify
                    (
                        pPublicKeyInfo,
                        pThisObject->pSignedData,
                        pThisObject->uSignedLength,
                        signType,
                        pSignature,
                        pBitString->uLength
                    );
}

BOOLEAN
AnscAsn1PKCS10InitName
    (
        ANSC_HANDLE                 hThisObject,
        PALCERTIFICATE_ATTRIBUTE    pAttrObject
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO
                                    pInfo;
    PANSC_ASN1_NAME                 pSubjectName;
    PANSC_ASN1_ATTRIBUTES           pAttributes;
    PCHAR                           pNameValue;
    PANSC_ASN1_PRINTABLESTRING      pPrintable;
    PANSC_ASN1_ATTRIBUTE            pAttribute;
    PANSC_ASN1_GENERALNAMES         pGeneralNames;
    PANSC_ASN1_EXTENSION            pExtension;
    PANSC_ASN1_EXTENSIONS           pExtensions;
    
    if( pThisObject == NULL || pAttrObject == NULL)
    {
        return FALSE;
    }

    /*
     *  init the name;
     */
    pSubjectName = (PANSC_ASN1_NAME)pThisObject->GetSubjectHandle(pThisObject);

    if( pSubjectName == NULL)
    {
        return FALSE;
    }

    if( !pSubjectName->InitAttribute(pSubjectName, pAttrObject))
    {
        return FALSE;
    }

    /*
     *  Check other attrs such as "Challenge password" ,"SubjectAltName"...
     */
    pInfo = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
            pThisObject->GetCertificateRequestInfo(pThisObject);

    if( pInfo == NULL)
    {
        return FALSE;
    }

    pAttributes = (PANSC_ASN1_ATTRIBUTES)pInfo->GetChildByIndex(pInfo,3);

    if( pAttributes == NULL)
    {
        return FALSE;
    }

    /* challenge password */
    pNameValue = pAttrObject->GetChallengePassword(pAttrObject);

    if( AnscSizeOfString(pNameValue) > 0)
    {
        pPrintable = AnscAsn1CreatePrintableString(NULL);

        if( pPrintable == NULL)
        {
            AnscTrace("Failed to create printable string.\n");

            return FALSE;
        }
        pPrintable->SetStringValue
            (
                pPrintable, 
                (PUCHAR)pNameValue,
                AnscSizeOfString(pNameValue)
            );

        pAttribute = (PANSC_ASN1_ATTRIBUTE)pAttributes->CreateChild(pAttributes, TRUE);

        if( pAttribute == NULL)
        {
            pPrintable->AsnFree(pPrintable);

            return FALSE;
        }

        /* Set ATTR_PKCS9CHALLENGEPASSWORD */
        pAttribute->SetTypeAndHandle
            (
                pAttribute, 
                "1.2.840.113549.1.9.7",
                pPrintable
            );

        pAttributes->bOptional = FALSE;
    }
    
    /* SubjectAltName */
    pNameValue = pAttrObject->GetSubjectAltName(pAttrObject);

    if( AnscSizeOfString(pNameValue) > 0)
    {
        pGeneralNames = (PANSC_ASN1_GENERALNAMES)AnscAsn1CreateGeneralNames(NULL);

        if( pGeneralNames == NULL)
        {
            return FALSE;
        }

        if( !pGeneralNames->AddAltName(pGeneralNames, pNameValue))
        {
            pGeneralNames->AsnFree(pGeneralNames);

            return FALSE;
        }

        pExtension = (PANSC_ASN1_EXTENSION)
            AnscAsn1ExtensionGenerate
                (
                    NULL,
                    "2.5.29.17",
                    FALSE,
                    pGeneralNames
                );

        if( pExtension == NULL)
        {
            pGeneralNames->AsnFree(pGeneralNames);

            return FALSE;
        }

        pExtensions = (PANSC_ASN1_EXTENSIONS)AnscAsn1CreateExtensions(NULL);

        if( pExtensions == NULL)
        {
            pExtension->AsnFree(pExtension);

            return FALSE;
        }

        pExtensions->AddChild(pExtensions, pExtension);

        pAttribute = (PANSC_ASN1_ATTRIBUTE)pAttributes->CreateChild(pAttributes, TRUE);

        if( pAttribute == NULL)
        {
            pExtensions->AsnFree(pExtensions);

            return FALSE;
        }

        /* Set ATTR_PKCS9EXTENDEDCERTIFICATEATTRIBUTES */
        pAttribute->SetTypeAndHandle
            (
                pAttribute, 
                "1.2.840.113549.1.9.14",
                pExtensions
            );

        pAttributes->bOptional = FALSE;
    }

    /*
     *  Set other information such as Signature type  and public key 
     */
    pThisObject->SetSignatureAlg(pThisObject, pAttrObject->SignAlgor);

    return TRUE;
}

BOOLEAN
AnscAsn1PKCS10SignWithKeyParam
    (
        ANSC_HANDLE                 hThisObject,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyPairHandle
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_PRIVATEKEYINFO       pKeyInfo;
    BOOLEAN                         bResult;

    pKeyInfo = (PANSC_ASN1_PRIVATEKEYINFO)
        AnscAsn1CreatePrivateKeyInfoWithKey(NULL, keyType, hKeyPairHandle);

    if( pKeyInfo == NULL)
    {
        return FALSE;
    }

    bResult = 
        pThisObject->SignWithPrivateKeyInfo
            (
                pThisObject,
                pKeyInfo
            );

    pKeyInfo->AsnFree(pKeyInfo);

    return bResult;
}

BOOLEAN
AnscAsn1PKCS10SignWithPrivateKeyInfo
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hPrivateKeyInfo
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_PRIVATEKEYINFO       pKeyInfo     = (PANSC_ASN1_PRIVATEKEYINFO)hPrivateKeyInfo;
    PUCHAR                          pSignature;
    ULONG                           uSignLength  = 1024;
    PANSC_ASN1_BITSTRING            pStringObject;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO
                                    pInfo;

    if( pThisObject == NULL)
    {
        return FALSE;
    }

    pInfo = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
            pThisObject->GetCertificateRequestInfo(pThisObject);

    if( pInfo == NULL)
    {
        return FALSE;
    }

    /* check the signed data */
    if( pThisObject->pSignedData == NULL || pThisObject->uSignedLength == 0)
    {
        pThisObject->pSignedData =
            pInfo->GetEncodedData(pInfo, &pThisObject->uSignedLength);
    }

    if( pThisObject->pSignedData == NULL)
    {
        return FALSE;
    }

    /* create the buffer to get the signature; */
    pSignature = (PUCHAR)AnscAllocateMemory(uSignLength);

    if( pSignature == NULL)
    {
        return FALSE;
    }

    if(ANSC_STATUS_SUCCESS != 
        pKeyInfo->SignData
            (
                pKeyInfo,
                pThisObject->pSignedData,
                pThisObject->uSignedLength,
                pThisObject->GetSignatureType(pThisObject),
                pSignature,
                &uSignLength
            ))
    {
        AnscFreeMemory(pSignature);

        return FALSE;
    }

    pStringObject = (PANSC_ASN1_BITSTRING)pThisObject->GetSignature(pThisObject);

    pStringObject->SetStringValue(pStringObject, pSignature, uSignLength);

    AnscFreeMemory(pSignature);

    return TRUE;
}

BOOLEAN
AnscAsn1PKCS10SignWithCryptAPI
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCryptAPI
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PCRYPT_API_STRUCT               pCrypto      = (PCRYPT_API_STRUCT)hCryptAPI;
    PUCHAR                          pSignature;
    ULONG                           uSignLength  = 1024;
    PANSC_ASN1_BITSTRING            pStringObject;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO
                                    pInfo;

    if( pThisObject == NULL || pCrypto == NULL || pCrypto->pSignData == NULL)
    {
        return FALSE;
    }

    pInfo = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
            pThisObject->GetCertificateRequestInfo(pThisObject);

    if( pInfo == NULL)
    {
        return FALSE;
    }

    /* check the signed data */
    if( pThisObject->pSignedData == NULL || pThisObject->uSignedLength == 0)
    {
        pThisObject->pSignedData =
            pInfo->GetEncodedData(pInfo, &pThisObject->uSignedLength);
    }

    if( pThisObject->pSignedData == NULL)
    {
        return FALSE;
    }

    /* create the buffer to get the signature; */
    pSignature = (PUCHAR)AnscAllocateMemory(uSignLength);

    if( pSignature == NULL)
    {
        return FALSE;
    }

    if(ANSC_STATUS_SUCCESS != 
        pCrypto->pSignData
            (
                pCrypto,
                pThisObject->pSignedData,
                pThisObject->uSignedLength,
                pThisObject->GetSignatureType(pThisObject),
                pSignature,
                &uSignLength
            ))
    {
        AnscFreeMemory(pSignature);

        return FALSE;
    }

    pStringObject = (PANSC_ASN1_BITSTRING)pThisObject->GetSignature(pThisObject);

    pStringObject->SetStringValue(pStringObject, pSignature, uSignLength);

    AnscFreeMemory(pSignature);

    return TRUE;

}

BOOLEAN
AnscAsn1PKCS10InitKeyPair
    (
        ANSC_HANDLE                 hThisObject,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyPairHandle
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject  = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PANSC_ASN1_SUBJECTPUBLICKEYINFO pPublicKeyInfo;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO
                                    pInfo;
    PANSC_ASN1_PRIVATEKEYINFO       pKeyInfo;
    BOOLEAN                         bResult;

    if( pThisObject == NULL || hKeyPairHandle == NULL)
    {
        return FALSE;
    }

    pInfo = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
            pThisObject->GetCertificateRequestInfo(pThisObject);

    if( pInfo == NULL)
    {
        return FALSE;
    }

    pPublicKeyInfo = (PANSC_ASN1_SUBJECTPUBLICKEYINFO)
        pInfo->GetChildByIndex(pInfo,2);

    if( pPublicKeyInfo == NULL)
    {
        return FALSE;
    }

    if(!pPublicKeyInfo->GenerateKey
        (
            pPublicKeyInfo,
            keyType,
            hKeyPairHandle
        ))
    {
        AnscTrace("Failed to set the public key.\n");

        return FALSE;
    }

    pKeyInfo = (PANSC_ASN1_PRIVATEKEYINFO)
        AnscAsn1CreatePrivateKeyInfoWithKey(NULL, keyType,hKeyPairHandle);

    if( pKeyInfo == NULL)
    {
        return FALSE;
    }

    bResult = 
        pThisObject->SignWithPrivateKeyInfo
            (
                pThisObject,
                pKeyInfo
            );

    pKeyInfo->AsnFree(pKeyInfo);

    return bResult;
}

BOOLEAN
AnscAsn1PKCS10InitWithCryptoAPI
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCryptAPI
    )
{
    PANSC_ASN1_CERTIFICATEREQUEST   pThisObject     = (PANSC_ASN1_CERTIFICATEREQUEST)hThisObject;
    PCRYPT_API_STRUCT               pCryptAPI       = (PCRYPT_API_STRUCT)hCryptAPI;
    PANSC_ASN1_SUBJECTPUBLICKEYINFO pPublicKeyInfo;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO
                                    pInfo;
    PKI_KEY_TYPE                    keyType;
    ANSC_CRYPTO_PUB_KEY_GEN_PARAMS  genParams;

    if( pThisObject == NULL || hCryptAPI == NULL)
    {
        return FALSE;
    }

    pInfo = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
            pThisObject->GetCertificateRequestInfo(pThisObject);

    if( pInfo == NULL)
    {
        return FALSE;
    }

    pPublicKeyInfo = (PANSC_ASN1_SUBJECTPUBLICKEYINFO)
        pInfo->GetChildByIndex(pInfo,2);

    if( pPublicKeyInfo == NULL)
    {
        return FALSE;
    }

    /* set the public key */
    pCryptAPI->pGetPublicKey(pCryptAPI,&keyType, &genParams);
    if(!pPublicKeyInfo->GenerateKey
        (
            pPublicKeyInfo,
            keyType,
            &genParams
        ))
    {
        AnscTrace("Failed to set the public key.\n");

        return FALSE;
    }

    /* sign it */
    pThisObject->SignWithCryptAPI(pThisObject, hCryptAPI);

    return TRUE;
}

/**********************************************************************

 OBJECT -- ANSC_ASN1_CERTIFICATIONREQUESTINFO

 CertificationRequestInfo ::= Sequence 
     {
                           version Integer 
                           subject Name 
                     subjectPKInfo SubjectPublicKeyInfo 
                        attributes [CON 0] IMP Attributes OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateCertificationRequestInfo
    (
        ANSC_HANDLE                 hReserved
    )
{
    UNREFERENCED_PARAMETER(hReserved);
    PANSC_ASN1_OBJECT               pChild;
    PANSC_ASN1_CERTIFICATIONREQUESTINFO 
                                    pThisObject  = NULL;

    /*
     * Create the base ASN.1 object.
     */
    pThisObject = (PANSC_ASN1_CERTIFICATIONREQUESTINFO)
        AnscAsn1CreateSequence
            (
                (ANSC_HANDLE)sizeof(ANSC_ASN1_CERTIFICATIONREQUESTINFO)
            );

    if( pThisObject == NULL)
    {
        return (ANSC_HANDLE)NULL;
    }

    /*
     * Initialize the common variables and functions for this ASN.1 object.
     */
    pThisObject->SetClassName(pThisObject, "ANSC_ASN1_CERTIFICATIONREQUESTINFO");
    pThisObject->SetName(pThisObject, "CertificationRequestInfo");

    pThisObject->Create             = AnscAsn1CreateCertificationRequestInfo;
    pThisObject->CreateChildAttr    = AnscAsn1CertificationRequestInfoCreateChildAttr;
    pThisObject->GetChildName       = AnscAsn1CertificationRequestInfoGetChildName;
    pThisObject->CreateChildObject  = AnscAsn1CertificationRequestInfoCreateChildObject;
    pThisObject->uTotalChild        = 4;

    /*
     * Create all the children
     */
    pThisObject->CreateAllChildren(pThisObject);


    /*
     *  Set the default values;
     */
    pChild  = pThisObject->GetChildByIndex(pThisObject,0);

    if( pChild != NULL)
    {
        ((PANSC_ASN1_INTEGER)pChild)->SetIntegerValue(pChild, 0);
    }

    return (ANSC_HANDLE)pThisObject;
}

ANSC_HANDLE
AnscAsn1CertificationRequestInfoCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    )
{
    PANSC_ASN1_OBJECT               pThisObject      = NULL;
    PANSC_ASN1_SEQUENCE             pParent          = (PANSC_ASN1_SEQUENCE)hThisObject;

    switch( index )
    {

        case 0:

            pThisObject = AnscAsn1CreateInteger(NULL);

            if( pThisObject != NULL)
            {
                pThisObject->AddAttribute(pThisObject, pParent->CreateChildAttr(pParent,index), FALSE);
                pThisObject->SetName(pThisObject, pParent->GetChildName(pParent,index));
                pThisObject->bCanBeOptional = TRUE;
                pThisObject->bOptional = TRUE;
            }

            break;

        case 1:

            pThisObject = AnscAsn1CreateName(NULL);

            if( pThisObject != NULL)
            {
                pThisObject->AddAttribute(pThisObject, pParent->CreateChildAttr(pParent,index), FALSE);
                pThisObject->SetName(pThisObject, pParent->GetChildName(pParent,index));
            }

            break;

        case 2:

            pThisObject = AnscAsn1CreateSubjectPublicKeyInfo(NULL);

            if( pThisObject != NULL)
            {
                pThisObject->AddAttribute(pThisObject, pParent->CreateChildAttr(pParent,index), FALSE);
                pThisObject->SetName(pThisObject, pParent->GetChildName(pParent,index));
            }

            break;

        case 3:

            pThisObject = AnscAsn1CreateAttributes(NULL);

            if( pThisObject != NULL)
            {
                pThisObject->AddAttribute(pThisObject, pParent->CreateChildAttr(pParent,index), FALSE);
                pThisObject->SetName(pThisObject, pParent->GetChildName(pParent,index));
                pThisObject->bCanBeOptional = TRUE;
                pThisObject->bOptional = TRUE;
            }

            break;

    }

    return pThisObject;

}

PANSC_ATTR_OBJECT
AnscAsn1CertificationRequestInfoCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    PANSC_ATTR_OBJECT               pAttrObject  = NULL;

    switch ( index )
    {
        case 0:
        case 1:
        case 2:

                break;

        case 3:

                pAttrObject = (PANSC_ATTR_OBJECT)
                    AnscAsn1AttrCreate
                        (
                          CONTEXT_FORM,
                          0,
                          IMPLICIT_TYPE
                        );

                break;

    }

    return pAttrObject;

}

PCHAR
AnscAsn1CertificationRequestInfoGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    switch ( index )
    {
        case 0:

            return"version";

        case 1:

            return"subject";

        case 2:

            return"subjectPKInfo";

        case 3:

            return"attributes";

    }

    return "";

}


#endif /* _PKI_KERNEL */

