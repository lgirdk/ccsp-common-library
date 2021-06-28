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

    MODULE: adv_pki_entity_internal.h

        ASN.1 ANSC Code Generated by Cisco Systems, Inc.

    ---------------------------------------------------------------

    DESCRIPTION:

        This interface is for the entity of PKI implementation.

        The entity is responsible for generating key pair, pkcs10
        certificate request, self-signed certificate.

    ---------------------------------------------------------------

    ENVIRONMENT:

        platform independent

    ---------------------------------------------------------------

    AUTHOR:

        Bin Zhu

    ---------------------------------------------------------------

    REVISION HISTORY:

        *   04/24/2003  initial revision

 **********************************************************************/


#ifndef  _ADV_PKI_ENTITY_INTERNAL_H
#define  _ADV_PKI_ENTITY_INTERNAL_H

ANSC_STATUS
AdvPKIEntityImportPKCS12
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pPKCS12Encoding,
        ULONG                       length,
        PCHAR                       pPassword
    );


ANSC_HANDLE
AdvPKIEntityExportPKCS12Handle
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pPass,
        BOOLEAN                     bExportCA
    );

PUCHAR
AdvPKIEntityExportPKCS12Encoding
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pPass,
        BOOLEAN                     bExportCA,
        PULONG                      pLength
    );

PUCHAR
AdvPKIEntityCreateSelfSignedCertEncoding
    (
        ANSC_HANDLE                 hThisObject,
        BOOLEAN                     bHasKeyIdentifier,
        PULONG                      pLength
    );

ANSC_HANDLE
AdvPKIEntityCreateSelfSignedCert
    (
        ANSC_HANDLE                 hThisObject,
        BOOLEAN                     bHasKeyIdentifier
    );

ANSC_STATUS
AdvPKIEntitySetIssuedPKCS7Certs
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pEncoding,
        ULONG                       length
    );

#endif  /*_ADV_PKI_ENTITY_INTERNAL_H*/


