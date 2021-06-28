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

    MODULE: ansc_asn1_PublicKey_internal.h

        ASN.1 ANSC Code Generated by Cisco Systems, Inc.

    ---------------------------------------------------------------

    DESCRIPTION:

        The Internal functions defined for ASN.1 objects

        *   ANSC_ASN1_PUBLICKEY
        *   ANSC_ASN1_RSAPUBLICKEY
        *   ANSC_ASN1_DSAPUBLICKEY
        *   ANSC_ASN1_DHPUBLICKEY
        *   ANSC_ASN1_KEYPAIR

    ---------------------------------------------------------------

    ENVIRONMENT:

        platform independent

    ---------------------------------------------------------------

    AUTHOR:

        ASNMAGIC ANSC CODE GENERATOR 1.0

    ---------------------------------------------------------------

    REVISION HISTORY:

        *   05/07/2002  initial revision
        *   08/09/2002  encryption functions are added
        *   08/13/2002  dhpublickey is added;
        *   08/14/2002  function added to check key matched or not

 **********************************************************************/


#ifndef  _ANSC_ASN1_PUBLICKEY_INTERNAL_H
#define  _ANSC_ASN1_PUBLICKEY_INTERNAL_H

/**********************************************************************

 OBJECT -- ANSC_ASN1_PUBLICKEY

 PublicKey ::= Choice 
     {
                      dsaPublicKey DSAPublicKey 
                      rsaPublicKey RSAPublicKey 
                      dhPublicKey  DHPublicKey
     }

 **********************************************************************/

ANSC_HANDLE
AnscAsn1PublicKeyCreateSelection
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PANSC_ATTR_OBJECT
AnscAsn1PublicKeyCreateSelectionAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       selType
    );

PCHAR
AnscAsn1PublicKeyGetSelectionName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       selType
    );

LONG
AnscAsn1PublicKeyGetChoiceByOID
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pOIDString
    );

PCHAR
AnscAsn1PublicKeyGetOIDValueByMask
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       selType
    );

/*
 *  Manually added functions;
 */
ANSC_STATUS
AnscAsn1PublicKeyVerify
    (
        ANSC_HANDLE                 hThisHandle,
        ANSC_HANDLE                 hParams,
        PUCHAR                      pDataSigned,
        ULONG                       lengthOfData,
        SIGNATURE_TYPE              signType,
        PUCHAR                      pSignature,
        ULONG                       uLength
    );

ANSC_STATUS
AnscAsn1PublicKeyEncrypt
    (
        ANSC_HANDLE                 pCryptHandle,           
        PUCHAR                      pDataWillBeEncrypted,
        ULONG                       lengthOfData,
        PUCHAR                      pDataEncrypted,
        PULONG                      pLength
    );

BOOLEAN
AnscAsn1PublicKeyIsKeyMatching
    (
        ANSC_HANDLE                 hThisHandle,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyParams
    );

ANSC_STATUS
AnscAsn1PublicKeyExportPublicKey
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyGenParams
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_RSAPUBLICKEY

 RSAPublicKey ::= Sequence 
     {
                           modulus Integer 
                    publicExponent Integer 
     }

 **********************************************************************/

PANSC_ATTR_OBJECT
AnscAsn1RSAPublicKeyCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PCHAR
AnscAsn1RSAPublicKeyGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_HANDLE
AnscAsn1RSAPublicKeyCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

/*
 *  Manually added functions;
 */
ANSC_STATUS
AnscAsn1RSAPublicKeyVerify
    (
        ANSC_HANDLE                 hThisHandle,
        ANSC_HANDLE                 hParams,
        PUCHAR                      pDataSigned,
        ULONG                       lengthOfData,
        SIGNATURE_TYPE              signType,
        PUCHAR                      pSignature,
        ULONG                       uLength
    );

BOOLEAN
AnscAsn1RSAPublicKeyInitKey
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyGenHandle
    );

ANSC_STATUS
AnscAsn1RSAPublicKeyEncrypt
    (
        ANSC_HANDLE                 pCryptHandle,           
        PUCHAR                      pDataWillBeEncrypted,
        ULONG                       lengthOfData,
        PUCHAR                      pDataEncrypted,
        PULONG                      pLength
    );

BOOLEAN
AnscAsn1RSAPublicKeyIsKeyMatching
    (
        ANSC_HANDLE                 hThisHandle,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyParams
    );

ANSC_STATUS
AnscAsn1RSAPublicKeyExportPublicKey
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyGenParams
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_DSAPUBLICKEY

 DSAPublicKey ::= Integer 

 **********************************************************************/

/*
 *  Manually added functions;
 */
ANSC_STATUS
AnscAsn1DSAPublicKeyVerify
    (
        ANSC_HANDLE                 hThisHandle,
        ANSC_HANDLE                 hParams,
        PUCHAR                      pDataSigned,
        ULONG                       lengthOfData,
        SIGNATURE_TYPE              signType,
        PUCHAR                      pSignature,
        ULONG                       uLength
    );

BOOLEAN
AnscAsn1DSAPublicKeyInitKey
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyGenHandle
    );

BOOLEAN
AnscAsn1DSAPublicKeyIsKeyMatching
    (
        ANSC_HANDLE                 hThisHandle,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyParams
    );

ANSC_STATUS
AnscAsn1DSAPublicKeyExportPublicKey
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyGenParams
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_DHPUBLICKEY

 DHPublicKey ::= Integer 

 **********************************************************************/

/*
 *  Manually added functions;
 */
BOOLEAN
AnscAsn1DHPublicKeyInitKey
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyGenHandle
    );

BOOLEAN
AnscAsn1DHPublicKeyIsKeyMatching
    (
        ANSC_HANDLE                 hThisHandle,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyParams
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_KEYPAIR

 KeyPair ::= Sequence 
     {
                           keyType Integer 
                            pubKey PublicKey
                            priKey PrivateKeyInfo
     }

 **********************************************************************/

PANSC_ATTR_OBJECT
AnscAsn1KeyPairCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PCHAR
AnscAsn1KeyPairGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_HANDLE
AnscAsn1KeyPairCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_STATUS
AnscAsn1KeyPairBeforeDecodingChild
    (
        ANSC_HANDLE                 hThisObject,
        int                         index,
        PVOID*                      ppEncoding
    );

ANSC_STATUS
AnscAsn1KeyPairInitKey
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       keyType,
        ANSC_HANDLE                 hKeyGenHandle
    );

ANSC_STATUS
AnscAsn1KeyPairExportKey
    (
        ANSC_HANDLE                 hThisObject,
        PULONG                      puKeyType,
        ANSC_HANDLE                 hKeyGenHandle
    );

#endif  /*_ANSC_ASN1_PUBLICKEY_INTERNAL_H*/

