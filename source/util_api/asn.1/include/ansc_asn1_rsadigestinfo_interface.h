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

    MODULE: ansc_asn1_RSADigestInfo_interface.h

        ASN.1 ANSC Code Generated by Cisco Systems, Inc.

    ---------------------------------------------------------------

    DESCRIPTION:

        The ASN.1 object defined in this file

        *   ANSC_ASN1_RSADIGESTINFO


    ---------------------------------------------------------------

    ENVIRONMENT:

        platform independent

    ---------------------------------------------------------------

    AUTHOR:

        ASNMAGIC ANSC CODE GENERATOR 1.0

    ---------------------------------------------------------------

    REVISION HISTORY:

        *   05/01/2002  initial revision

 **********************************************************************/


#ifndef  _ANSC_ASN1_RSADIGESTINFO_INTERFACE_H
#define  _ANSC_ASN1_RSADIGESTINFO_INTERFACE_H

/**********************************************************************

 OBJECT -- ANSC_ASN1_RSADIGESTINFO

 RSADigestInfo ::= Sequence 
     {
                     algIdentifier AlgorithmIdentifier 
                     messageDigest OctetString 
     }

 **********************************************************************/

#define  ANSC_ASN1_RSADIGESTINFO_CLASS_CONTENT          ANSC_ASN1_SEQUENCE_CLASS_CONTENT

typedef  struct
_ANSC_ASN1_RSADIGESTINFO
{
    ANSC_ASN1_RSADIGESTINFO_CLASS_CONTENT
}
ANSC_ASN1_RSADIGESTINFO,  *PANSC_ASN1_RSADIGESTINFO;

#define  ACCESS_ANSC_ASN1_RSADIGESTINFO(p)    \
         ACCESS_CONTAINER(p, ANSC_ASN1_RSADIGESTINFO, Linkage)


#endif  /*_ANSC_ASN1_RSADIGESTINFO_INTERFACE_H*/


