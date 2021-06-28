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

    MODULE: asn1_ocsprequest_export_api.h

        ASN.1 ANSC Code Generated by Cisco Systems, Inc.

    ---------------------------------------------------------------

    DESCRIPTION:

        The Internal functions defined for ASN.1 objects

        *   ASN1_OCSPREQUEST
        *   ASN1_OCSPTBSREQUEST
        *   ASN1_ALGORANDSIGNATURE
        *   ASN1_OCSPVERSION
        *   ASN1_REQUESTLIST
        *   ASN1_OREQUEST
        *   ASN1_OCSPCERTID
        *   ASN1_OCSPRESPONSE
        *   ASN1_OCSPRESPONSESTATUS
        *   ASN1_RESPONSEBYTES
        *   ASN1_BASICOCSPRESPONSE
        *   ASN1_RESPONSEDATA
        *   ASN1_RESPONDERID
        *   ASN1_MULTIRESPONSES
        *   ASN1_SINGLERESPONSE
        *   ASN1_KEYHASH
        *   ASN1_OCSPCERTSTATUS
        *   ASN1_REVOKEDINFO
        *   ASN1_UNKNOWNINFO
        *   ASN1_ARCHIVECUTOFF
        *   ASN1_ACCEPTABLERESPONSES
        *   ASN1_SERVICELOCATOR
        *   ASN1_CERTIFICATESEQ


    ---------------------------------------------------------------

    ENVIRONMENT:

        platform independent

    ---------------------------------------------------------------

    AUTHOR:

        ASNMAGIC ANSC CODE GENERATOR 1.0

    ---------------------------------------------------------------

    REVISION HISTORY:

        *   12/13/2002  initial revision

 **********************************************************************/


#ifndef  _ASN1_OCSPREQUEST_EXPORTED_API_H
#define  _ASN1_OCSPREQUEST_EXPORTED_API_H

/**********************************************************************

 OBJECT -- ASN1_OCSPREQUEST

 OCSPRequest ::= Sequence 
     {
                        tbsRequest OCSPtbsRequest 
                         signature [CON 0] AlgorAndSignature OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateOCSPRequest
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_OCSPTBSREQUEST

 OCSPtbsRequest ::= Sequence 
     {
                           version [CON 0] OCSPVersion 
                     requestorName [CON 1] GeneralName OPT
                       requestList RequestList 
                 requestExtensions [CON 2] Extensions OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateOCSPtbsRequest
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_ALGORANDSIGNATURE

 AlgorAndSignature ::= Sequence 
     {
                signatureAlgorithm AlgorithmIdentifier 
                         signature BitString 
                              cert [CON 0] CertificateSeq OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateAlgorAndSignature
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_OCSPVERSION

 OCSPVersion ::= Integer 

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateOCSPVersion
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_REQUESTLIST

 RequestList ::= SequenceOf ORequest  {}

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateRequestList
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_OREQUEST

 ORequest ::= Sequence 
     {
                           reqCert OCSPCertID 
           singleRequestExtensions [CON 0] Extensions OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateORequest
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_OCSPCERTID

 OCSPCertID ::= Sequence 
     {
                     hashAlgorithm AlgorithmIdentifier 
                    hashOfIssuerDN OctetString 
             hashOfIssuerPublicKey OctetString 
                      serialNumber CertificateSerialNumber 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateOCSPCertID
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_OCSPRESPONSE

 OCSPResponse ::= Sequence 
     {
                    responseStatus OCSPResponseStatus 
                     responseBytes [CON 0] ResponseBytes OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateOCSPResponse
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_OCSPRESPONSESTATUS

 OCSPResponseStatus ::= Enumerate 

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateOCSPResponseStatus
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_RESPONSEBYTES

 ResponseBytes ::= Sequence 
     {
                      responseType OID 
                      responseData OctetString 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateResponseBytes
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_BASICOCSPRESPONSE

 BasicOCSPResponse ::= Sequence 
     {
                   tbsResponseData ResponseData 
                    signatureAlgor AlgorithmIdentifier 
                         signature BitString 
                             certs [CON 0] CertificateSeq OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateBasicOCSPResponse
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_RESPONSEDATA

 ResponseData ::= Sequence 
     {
                           version [CON 0] OCSPVersion 
                       responderID ResponderID 
                        producedAt GeneralizedTime 
                         responses MultiResponses 
                responseExtensions [CON 1] Extensions OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateResponseData
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_RESPONDERID

 ResponderID ::= Choice 
     {
                            byName [CON 1] IMP Name 
                             byKey [CON 2] IMP KeyHash 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateResponderID
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_MULTIRESPONSES

 MultiResponses ::= SequenceOf SingleResponse  {}

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateMultiResponses
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_SINGLERESPONSE

 SingleResponse ::= Sequence 
     {
                            certID OCSPCertID 
                        certStatus OCSPCertStatus 
                        thisUpdate GeneralizedTime 
                        nextUpdate [CON 0] GeneralizedTime OPT
                  singleExtensions [CON 1] Extensions OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateSingleResponse
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_KEYHASH

 KeyHash ::= OctetString 

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateKeyHash
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_OCSPCERTSTATUS

 OCSPCertStatus ::= Choice 
     {
                              good [CON 0] IMP NULL 
                           revoked [CON 1] IMP RevokedInfo 
                           unknown [CON 2] IMP UnknownInfo 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateOCSPCertStatus
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_REVOKEDINFO

 RevokedInfo ::= Sequence 
     {
                    revocationTime GeneralizedTime 
                  revocationReason [CON 0] CRLReason OPT
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateRevokedInfo
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_UNKNOWNINFO

 UnknownInfo ::= Choice 
     {
                           unknown NULL 
                            reason Enumerate 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateUnknownInfo
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_ARCHIVECUTOFF

 ArchiveCutoff ::= GeneralizedTime 

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateArchiveCutoff
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_ACCEPTABLERESPONSES

 AcceptableResponses ::= SequenceOf OID  {}

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateAcceptableResponses
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_SERVICELOCATOR

 ServiceLocator ::= Sequence 
     {
                       serviceName Name 
                           locator AuthorityInfoAccessSyntax 
     }

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateServiceLocator
    (
        ANSC_HANDLE                 hReserved
    );

/**********************************************************************

 OBJECT -- ASN1_CERTIFICATESEQ

 CertificateSeq ::= SequenceOf Certificate  {}

 **********************************************************************/

ANSC_HANDLE 
AnscAsn1CreateCertificateSeq
    (
        ANSC_HANDLE                 hReserved
    );


#endif  /* _ASN1_OCSPREQUEST_EXPORTED_API_H */

