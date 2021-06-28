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

    MODULE: ansc_asn1_Name_export_api.h

        ASN.1 ANSC Code Generated by Cisco Systems, Inc.

    ---------------------------------------------------------------

    DESCRIPTION:

        The Internal functions defined for ASN.1 objects

        *   ANSC_ASN1_NAME
        *   ANSC_ASN1_RDNSEQUENCE
        *   ANSC_ASN1_ATTRIBUTE
        *   ANSC_ASN1_RELATIVEDISTINGUISHEDNAME
        *   ANSC_ASN1_ATTRIBUTETYPEANDVALUE
        *   ANSC_ASN1_ATTRIBUTEVALUES
        *   ANSC_ASN1_ATTRIBUTEVALUE
        *   ANSC_ASN1_X520NAME
        *   ANSC_ASN1_UNSTRUCTUREDNAME
        *   ANSC_ASN1_DIRECTORYSTRING
        *   ANSC_ASN1_MESSAGEDIGEST
        *   ANSC_ASN1_SIGNINGTIME
        *   ANSC_ASN1_CHLLENGEPASSWORD
        *   ANSC_ASN1_UNSTRUCTUREDADDRESS
        *   ANSC_ASN1_CONTENTTYPE
        *   ANSC_ASN1_X520COMMONNAME
        *   ANSC_ASN1_X520LOCALITYNAME


    ---------------------------------------------------------------

    ENVIRONMENT:

        platform independent

    ---------------------------------------------------------------

    AUTHOR:

        ASNMAGIC ANSC CODE GENERATOR 1.0

    ---------------------------------------------------------------

    REVISION HISTORY:

        *   05/07/2002  initial revision

 **********************************************************************/


#ifndef  _ANSC_ASN1_NAME_EXPORTED_API_H
#define  _ANSC_ASN1_NAME_EXPORTED_API_H

/**********************************************************************

 OBJECT -- ANSC_ASN1_NAME

 Name ::= Choice 
     {
                       rdnSequence RDNSequence 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateName
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_RDNSEQUENCE

 RDNSequence ::= SequenceOf RelativeDistinguishedName  {}

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateRDNSequence
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_ATTRIBUTE

 Attribute ::= Sequence 
     {
                     attributeType OID 
                             value AttributeValues 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateAttribute
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_RELATIVEDISTINGUISHEDNAME

 RelativeDistinguishedName ::= SetOf AttributeTypeAndValue  {}

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateRelativeDistinguishedName
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_ATTRIBUTETYPEANDVALUE

 AttributeTypeAndValue ::= Sequence 
     {
                     attributeType OID 
                             value AttributeValue 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateAttributeTypeAndValue
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_ATTRIBUTEVALUES

 AttributeValues ::= SetOf AttributeValue  {}

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateAttributeValues
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_ATTRIBUTEVALUE

 AttributeValue ::= Choice 
     {
                   x520dnQualifier PrintableString 
                       countryName PrintableString 
                 pkcs9EmailAddress IA5String 
                       contentType ContentType 
                  unstructuredName UnstructuredName 
                     messageDigest MessageDigest 
                       signingTime SigningTime 
                 challengePassword ChllengePassword 
               unstructuredAddress UnstructuredAddress 
                         bmpString BMPString 
                          x520Name X520name 
                    x520CommonName X520CommonName 
                        signerInfo SignerInfo 
                   pkcs9LocalKeyID OctetString 
                          keyUsage BitString 
                        utf8String UTF8String 
                      genderString PrintableString 
              printableCountryName PrintableString 
                      localityName X520LocalityName 
                   domainComponent DirectoryString 
                         t61String TeletexString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateAttributeValue
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_X520NAME

 X520name ::= Choice 
     {
                     teletexString TeletexString 
                   printableString PrintableString 
                   universalString UniversalString 
                        utf8String UTF8String 
                         bmpString BMPString 
                       octetString OctetString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateX520name
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_UNSTRUCTUREDNAME

 UnstructuredName ::= Choice 
     {
                         iA5String IA5String 
                   universalString UniversalString 
                   printableString PrintableString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateUnstructuredName
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_DIRECTORYSTRING

 DirectoryString ::= Choice 
     {
                     teletexString TeletexString 
                   printableString PrintableString 
                   universalString UniversalString 
                        utf8String UTF8String 
                         bmpString BMPString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateDirectoryString
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_MESSAGEDIGEST

 MessageDigest ::= OctetString 

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateMessageDigest
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_SIGNINGTIME

 SigningTime ::= Time 

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateSigningTime
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_CHLLENGEPASSWORD

 ChllengePassword ::= Choice 
     {
                   printableString PrintableString 
                         t61String TeletexString 
                   universalString UniversalString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateChllengePassword
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_UNSTRUCTUREDADDRESS

 UnstructuredAddress ::= Choice 
     {
                   printableString PrintableString 
                         t61String TeletexString 
                   universalString UniversalString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateUnstructuredAddress
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_CONTENTTYPE

 ContentType ::= OID 

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateContentType
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_X520COMMONNAME

 X520CommonName ::= Choice 
     {
                     teletexString TeletexString 
                   printableString PrintableString 
                   universalString UniversalString 
                        utf8String UTF8String 
                         bmpString BMPString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateX520CommonName
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_X520LOCALITYNAME

 X520LocalityName ::= Choice 
     {
                     teletexString TeletexString 
                   printableString PrintableString 
                   universalString UniversalString 
                        utf8String UTF8String 
                         bmpString BMPString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateX520LocalityName
    (
        ANSC_HANDLE                 hReserved
    );


#endif  /*_ANSC_ASN1_NAME_EXPORTED_API_H*/


