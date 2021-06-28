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

    MODULE: asn1_ocsprequest_interface.h

        ASN.1 ANSC Code Generated by Cisco Systems, Inc.

    ---------------------------------------------------------------

    DESCRIPTION:

        The ASN.1 object defined in this file

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


#ifndef  _ASN1_OCSPREQUEST_INTERFACE_H
#define  _ASN1_OCSPREQUEST_INTERFACE_H

/**********************************************************************

 OBJECT -- ASN1_OCSPREQUEST

 OCSPRequest ::= Sequence 
     {
                        tbsRequest OCSPtbsRequest 
                         signature [CON 0] AlgorAndSignature OPT
     }

 **********************************************************************/

#define  ANSC_ASN1_OCSPREQUEST_CLASS_CONTENT                          \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetTbsRequest;                    \
    PFN_ASN1_GET_CHILD              GetSignature;                     \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_OCSPREQUEST
{
    ANSC_ASN1_OCSPREQUEST_CLASS_CONTENT
}
ANSC_ASN1_OCSPREQUEST,  *PANSC_ASN1_OCSPREQUEST;

#define  ACCESS_ANSC_ASN1_OCSPREQUEST(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_OCSPREQUEST, Linkage)

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

#define  ANSC_ASN1_OCSPTBSREQUEST_CLASS_CONTENT                       \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetVersion;                       \
    PFN_ASN1_GET_CHILD              GetRequestorName;                 \
    PFN_ASN1_GET_CHILD              GetRequestList;                   \
    PFN_ASN1_GET_CHILD              GetRequestExtensions;             \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_OCSPTBSREQUEST
{
    ANSC_ASN1_OCSPTBSREQUEST_CLASS_CONTENT
}
ANSC_ASN1_OCSPTBSREQUEST,  *PANSC_ASN1_OCSPTBSREQUEST;

#define  ACCESS_ANSC_ASN1_OCSPTBSREQUEST(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_OCSPTBSREQUEST, Linkage)

/**********************************************************************

 OBJECT -- ASN1_ALGORANDSIGNATURE

 AlgorAndSignature ::= Sequence 
     {
                signatureAlgorithm AlgorithmIdentifier 
                         signature BitString 
                              cert [CON 0] CertificateSeq OPT
     }

 **********************************************************************/

#define  ANSC_ASN1_ALGORANDSIGNATURE_CLASS_CONTENT                    \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetSignatureAlgorithm;            \
    PFN_ASN1_GET_CHILD              GetSignature;                     \
    PFN_ASN1_GET_CHILD              GetCert;                          \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_ALGORANDSIGNATURE
{
    ANSC_ASN1_ALGORANDSIGNATURE_CLASS_CONTENT
}
ANSC_ASN1_ALGORANDSIGNATURE,  *PANSC_ASN1_ALGORANDSIGNATURE;

#define  ACCESS_ANSC_ASN1_ALGORANDSIGNATURE(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_ALGORANDSIGNATURE, Linkage)

/**********************************************************************

 OBJECT -- ASN1_OCSPVERSION

 OCSPVersion ::= Integer 

 **********************************************************************/

#define  ANSC_ASN1_OCSPVERSION_CLASS_CONTENT                          \
    /* duplication of the base object class content */                \
    ANSC_ASN1_INTEGER_CLASS_CONTENT                                   \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_OCSPVERSION
{
    ANSC_ASN1_OCSPVERSION_CLASS_CONTENT
}
ANSC_ASN1_OCSPVERSION,  *PANSC_ASN1_OCSPVERSION;

#define  ACCESS_ANSC_ASN1_OCSPVERSION(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_OCSPVERSION, Linkage)

/**********************************************************************

 OBJECT -- ASN1_REQUESTLIST

 RequestList ::= SequenceOf ORequest  {}

 **********************************************************************/

#define  ANSC_ASN1_REQUESTLIST_CLASS_CONTENT                          \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCEOF_CLASS_CONTENT                                \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_REQUESTLIST
{
    ANSC_ASN1_REQUESTLIST_CLASS_CONTENT
}
ANSC_ASN1_REQUESTLIST,  *PANSC_ASN1_REQUESTLIST;

#define  ACCESS_ANSC_ASN1_REQUESTLIST(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_REQUESTLIST, Linkage)

/**********************************************************************

 OBJECT -- ASN1_OREQUEST

 ORequest ::= Sequence 
     {
                           reqCert OCSPCertID 
           singleRequestExtensions [CON 0] Extensions OPT
     }

 **********************************************************************/

#define  ANSC_ASN1_OREQUEST_CLASS_CONTENT                             \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetReqCert;                       \
    PFN_ASN1_GET_CHILD              GetSingleRequestExtensions;       \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_OREQUEST
{
    ANSC_ASN1_OREQUEST_CLASS_CONTENT
}
ANSC_ASN1_OREQUEST,  *PANSC_ASN1_OREQUEST;

#define  ACCESS_ANSC_ASN1_OREQUEST(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_OREQUEST, Linkage)

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

#define  ANSC_ASN1_OCSPCERTID_CLASS_CONTENT                           \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetHashAlgorithm;                 \
    PFN_ASN1_GET_CHILD              GetHashOfIssuerDN;                \
    PFN_ASN1_GET_CHILD              GetHashOfIssuerPublicKey;         \
    PFN_ASN1_GET_CHILD              GetSerialNumber;                  \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_OCSPCERTID
{
    ANSC_ASN1_OCSPCERTID_CLASS_CONTENT
}
ANSC_ASN1_OCSPCERTID,  *PANSC_ASN1_OCSPCERTID;

#define  ACCESS_ANSC_ASN1_OCSPCERTID(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_OCSPCERTID, Linkage)

/**********************************************************************

 OBJECT -- ASN1_OCSPRESPONSE

 OCSPResponse ::= Sequence 
     {
                    responseStatus OCSPResponseStatus 
                     responseBytes [CON 0] ResponseBytes OPT
     }

 **********************************************************************/

#define  ANSC_ASN1_OCSPRESPONSE_CLASS_CONTENT                         \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetResponseStatus;                \
    PFN_ASN1_GET_CHILD              GetResponseBytes;                 \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_OCSPRESPONSE
{
    ANSC_ASN1_OCSPRESPONSE_CLASS_CONTENT
}
ANSC_ASN1_OCSPRESPONSE,  *PANSC_ASN1_OCSPRESPONSE;

#define  ACCESS_ANSC_ASN1_OCSPRESPONSE(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_OCSPRESPONSE, Linkage)

/**********************************************************************

 OBJECT -- ASN1_OCSPRESPONSESTATUS

 OCSPResponseStatus ::= Enumerate 

 **********************************************************************/

#define  ANSC_ASN1_OCSPRESPONSESTATUS_CLASS_CONTENT                   \
    /* duplication of the base object class content */                \
    ANSC_ASN1_ENUMERATE_CLASS_CONTENT                                 \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_OCSPRESPONSESTATUS
{
    ANSC_ASN1_OCSPRESPONSESTATUS_CLASS_CONTENT
}
ANSC_ASN1_OCSPRESPONSESTATUS,  *PANSC_ASN1_OCSPRESPONSESTATUS;

#define  ACCESS_ANSC_ASN1_OCSPRESPONSESTATUS(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_OCSPRESPONSESTATUS, Linkage)

/**********************************************************************

 OBJECT -- ASN1_RESPONSEBYTES

 ResponseBytes ::= Sequence 
     {
                      responseType OID 
                      responseData OctetString 
     }

 **********************************************************************/

#define  ANSC_ASN1_RESPONSEBYTES_CLASS_CONTENT                        \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetResponseType;                  \
    PFN_ASN1_GET_CHILD              GetResponseData;                  \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_RESPONSEBYTES
{
    ANSC_ASN1_RESPONSEBYTES_CLASS_CONTENT
}
ANSC_ASN1_RESPONSEBYTES,  *PANSC_ASN1_RESPONSEBYTES;

#define  ACCESS_ANSC_ASN1_RESPONSEBYTES(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_RESPONSEBYTES, Linkage)

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

#define  ANSC_ASN1_BASICOCSPRESPONSE_CLASS_CONTENT                    \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetTbsResponseData;               \
    PFN_ASN1_GET_CHILD              GetSignatureAlgor;                \
    PFN_ASN1_GET_CHILD              GetSignature;                     \
    PFN_ASN1_GET_CHILD              GetCerts;                         \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_BASICOCSPRESPONSE
{
    ANSC_ASN1_BASICOCSPRESPONSE_CLASS_CONTENT
}
ANSC_ASN1_BASICOCSPRESPONSE,  *PANSC_ASN1_BASICOCSPRESPONSE;

#define  ACCESS_ANSC_ASN1_BASICOCSPRESPONSE(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_BASICOCSPRESPONSE, Linkage)

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

#define  ANSC_ASN1_RESPONSEDATA_CLASS_CONTENT                         \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetVersion;                       \
    PFN_ASN1_GET_CHILD              GetResponderID;                   \
    PFN_ASN1_GET_CHILD              GetProducedAt;                    \
    PFN_ASN1_GET_CHILD              GetResponses;                     \
    PFN_ASN1_GET_CHILD              GetResponseExtensions;            \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_RESPONSEDATA
{
    ANSC_ASN1_RESPONSEDATA_CLASS_CONTENT
}
ANSC_ASN1_RESPONSEDATA,  *PANSC_ASN1_RESPONSEDATA;

#define  ACCESS_ANSC_ASN1_RESPONSEDATA(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_RESPONSEDATA, Linkage)

/**********************************************************************

 OBJECT -- ASN1_RESPONDERID

 ResponderID ::= Choice 
     {
                            byName [CON 1] IMP Name 
                             byKey [CON 2] IMP KeyHash 
     }

 **********************************************************************/

#define  RESPONDERID_MASK_BYNAME                                   0x00
#define  RESPONDERID_MASK_BYKEY                                    0x01
#define  RESPONDERID_MAXI_MASK                                     0x01

#define  ANSC_ASN1_RESPONDERID_CLASS_CONTENT                          \
    /* duplication of the base object class content */                \
    ANSC_ASN1_CHOICE_CLASS_CONTENT                                    \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_RESPONDERID
{
    ANSC_ASN1_RESPONDERID_CLASS_CONTENT
}
ANSC_ASN1_RESPONDERID,  *PANSC_ASN1_RESPONDERID;

#define  ACCESS_ANSC_ASN1_RESPONDERID(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_RESPONDERID, Linkage)

/**********************************************************************

 OBJECT -- ASN1_MULTIRESPONSES

 MultiResponses ::= SequenceOf SingleResponse  {}

 **********************************************************************/

#define  ANSC_ASN1_MULTIRESPONSES_CLASS_CONTENT                       \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCEOF_CLASS_CONTENT                                \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_MULTIRESPONSES
{
    ANSC_ASN1_MULTIRESPONSES_CLASS_CONTENT
}
ANSC_ASN1_MULTIRESPONSES,  *PANSC_ASN1_MULTIRESPONSES;

#define  ACCESS_ANSC_ASN1_MULTIRESPONSES(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_MULTIRESPONSES, Linkage)

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

#define  ANSC_ASN1_SINGLERESPONSE_CLASS_CONTENT                       \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetCertID;                        \
    PFN_ASN1_GET_CHILD              GetCertStatus;                    \
    PFN_ASN1_GET_CHILD              GetThisUpdate;                    \
    PFN_ASN1_GET_CHILD              GetNextUpdate;                    \
    PFN_ASN1_GET_CHILD              GetSingleExtensions;              \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_SINGLERESPONSE
{
    ANSC_ASN1_SINGLERESPONSE_CLASS_CONTENT
}
ANSC_ASN1_SINGLERESPONSE,  *PANSC_ASN1_SINGLERESPONSE;

#define  ACCESS_ANSC_ASN1_SINGLERESPONSE(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_SINGLERESPONSE, Linkage)

/**********************************************************************

 OBJECT -- ASN1_KEYHASH

 KeyHash ::= OctetString 

 **********************************************************************/

#define  ANSC_ASN1_KEYHASH_CLASS_CONTENT                              \
    /* duplication of the base object class content */                \
    ANSC_ASN1_STRING_CLASS_CONTENT                                    \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_KEYHASH
{
    ANSC_ASN1_KEYHASH_CLASS_CONTENT
}
ANSC_ASN1_KEYHASH,  *PANSC_ASN1_KEYHASH;

#define  ACCESS_ANSC_ASN1_KEYHASH(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_KEYHASH, Linkage)

/**********************************************************************

 OBJECT -- ASN1_OCSPCERTSTATUS

 OCSPCertStatus ::= Choice 
     {
                              good [CON 0] IMP NULL 
                           revoked [CON 1] IMP RevokedInfo 
                           unknown [CON 2] IMP UnknownInfo 
     }

 **********************************************************************/

#define  OCSPCERTSTATUS_MASK_GOOD                                  0x00
#define  OCSPCERTSTATUS_MASK_REVOKED                               0x01
#define  OCSPCERTSTATUS_MASK_UNKNOWN                               0x02
#define  OCSPCERTSTATUS_MAXI_MASK                                  0x02

#define  ANSC_ASN1_OCSPCERTSTATUS_CLASS_CONTENT                       \
    /* duplication of the base object class content */                \
    ANSC_ASN1_CHOICE_CLASS_CONTENT                                    \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_OCSPCERTSTATUS
{
    ANSC_ASN1_OCSPCERTSTATUS_CLASS_CONTENT
}
ANSC_ASN1_OCSPCERTSTATUS,  *PANSC_ASN1_OCSPCERTSTATUS;

#define  ACCESS_ANSC_ASN1_OCSPCERTSTATUS(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_OCSPCERTSTATUS, Linkage)

/**********************************************************************

 OBJECT -- ASN1_REVOKEDINFO

 RevokedInfo ::= Sequence 
     {
                    revocationTime GeneralizedTime 
                  revocationReason [CON 0] CRLReason OPT
     }

 **********************************************************************/

#define  ANSC_ASN1_REVOKEDINFO_CLASS_CONTENT                          \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetRevocationTime;                \
    PFN_ASN1_GET_CHILD              GetRevocationReason;              \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_REVOKEDINFO
{
    ANSC_ASN1_REVOKEDINFO_CLASS_CONTENT
}
ANSC_ASN1_REVOKEDINFO,  *PANSC_ASN1_REVOKEDINFO;

#define  ACCESS_ANSC_ASN1_REVOKEDINFO(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_REVOKEDINFO, Linkage)

/**********************************************************************

 OBJECT -- ASN1_UNKNOWNINFO

 UnknownInfo ::= Choice 
     {
                           unknown NULL 
                            reason Enumerate 
     }

 **********************************************************************/

#define  UNKNOWNINFO_MASK_UNKNOWN                                  0x00
#define  UNKNOWNINFO_MASK_REASON                                   0x01
#define  UNKNOWNINFO_MAXI_MASK                                     0x01

#define  ANSC_ASN1_UNKNOWNINFO_CLASS_CONTENT                          \
    /* duplication of the base object class content */                \
    ANSC_ASN1_CHOICE_CLASS_CONTENT                                    \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_UNKNOWNINFO
{
    ANSC_ASN1_UNKNOWNINFO_CLASS_CONTENT
}
ANSC_ASN1_UNKNOWNINFO,  *PANSC_ASN1_UNKNOWNINFO;

#define  ACCESS_ANSC_ASN1_UNKNOWNINFO(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_UNKNOWNINFO, Linkage)

/**********************************************************************

 OBJECT -- ASN1_ARCHIVECUTOFF

 ArchiveCutoff ::= GeneralizedTime 

 **********************************************************************/

#define  ANSC_ASN1_ARCHIVECUTOFF_CLASS_CONTENT                        \
    /* duplication of the base object class content */                \
    ANSC_ASN1_ALTIME_CLASS_CONTENT                                    \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_ARCHIVECUTOFF
{
    ANSC_ASN1_ARCHIVECUTOFF_CLASS_CONTENT
}
ANSC_ASN1_ARCHIVECUTOFF,  *PANSC_ASN1_ARCHIVECUTOFF;

#define  ACCESS_ANSC_ASN1_ARCHIVECUTOFF(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_ARCHIVECUTOFF, Linkage)

/**********************************************************************

 OBJECT -- ASN1_ACCEPTABLERESPONSES

 AcceptableResponses ::= SequenceOf OID  {}

 **********************************************************************/

#define  ANSC_ASN1_ACCEPTABLERESPONSES_CLASS_CONTENT                  \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCEOF_CLASS_CONTENT                                \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_ACCEPTABLERESPONSES
{
    ANSC_ASN1_ACCEPTABLERESPONSES_CLASS_CONTENT
}
ANSC_ASN1_ACCEPTABLERESPONSES,  *PANSC_ASN1_ACCEPTABLERESPONSES;

#define  ACCESS_ANSC_ASN1_ACCEPTABLERESPONSES(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_ACCEPTABLERESPONSES, Linkage)

/**********************************************************************

 OBJECT -- ASN1_SERVICELOCATOR

 ServiceLocator ::= Sequence 
     {
                       serviceName Name 
                           locator AuthorityInfoAccessSyntax 
     }

 **********************************************************************/

#define  ANSC_ASN1_SERVICELOCATOR_CLASS_CONTENT                       \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCE_CLASS_CONTENT                                  \
    /* start of object class content */                               \
    PFN_ASN1_GET_CHILD              GetServiceName;                   \
    PFN_ASN1_GET_CHILD              GetLocator;                       \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_SERVICELOCATOR
{
    ANSC_ASN1_SERVICELOCATOR_CLASS_CONTENT
}
ANSC_ASN1_SERVICELOCATOR,  *PANSC_ASN1_SERVICELOCATOR;

#define  ACCESS_ANSC_ASN1_SERVICELOCATOR(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_SERVICELOCATOR, Linkage)

/**********************************************************************

 OBJECT -- ASN1_CERTIFICATESEQ

 CertificateSeq ::= SequenceOf Certificate  {}

 **********************************************************************/

#define  ANSC_ASN1_CERTIFICATESEQ_CLASS_CONTENT                       \
    /* duplication of the base object class content */                \
    ANSC_ASN1_SEQUENCEOF_CLASS_CONTENT                                \
    /* start of object class content */                               \
    /* end of object class content */                                 \

typedef  struct
_ANSC_ASN1_CERTIFICATESEQ
{
    ANSC_ASN1_CERTIFICATESEQ_CLASS_CONTENT
}
ANSC_ASN1_CERTIFICATESEQ,  *PANSC_ASN1_CERTIFICATESEQ;

#define  ACCESS_ANSC_ASN1_CERTIFICATESEQ(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_CERTIFICATESEQ, Linkage)


#endif  /* _ASN1_OCSPREQUEST_INTERFACE_H */

