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

    module:	dslh_ifo_mco.h

        For DSL Home Model Implementation (DSLH),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco System  , Inc., 1997 ~ 2005
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This wrapper file defines the base class data structure and
        interface for the Dslh Management Client Operation Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        09/01/05    initial revision.

**********************************************************************/


#ifndef  _DSLH_IFO_MCO_
#define  _DSLH_IFO_MCO_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_ifo_interface.h"


/***********************************************************
    DSLH MANAGEMENT CLIENT OPERATION INTERFACE DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the os wrapper object definition.
 */
#define  DSLH_MCO_INTERFACE_NAME                    "dslhManagementClientOperationIf"
#define  DSLH_MCO_INTERFACE_ID                      0

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support), we
 * have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */
typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_REGISTER)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hActionContext,
        void*                       pfnAction
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_NOTIFY)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bNoMoreRequests,
        BOOL                        bHoldRequests
    );

typedef  ULONG
(*PFN_DSLHMCOIF_GET_TYPE)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_PROCESS)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSoapResponse
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_PROCESS2)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pMethodName,
        ANSC_HANDLE                 hSoapFault
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_INVOKE)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pMethodName
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_GET_METHODS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_SET_PARAM_V)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamValueArray,
        ULONG                       ulArraySize,
        char*                       pParamKey
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_GET_PARAM_V)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pParamNameArray
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_GET_PARAM_N)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pParamPath,
        BOOL                        bNextLevel
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_SET_PARAM_A)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSetParamAttribArray,
        ULONG                       ulArraySize
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_GET_PARAM_A)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pParamNameArray
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_ADD_OBJECT)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pObjectName,
        char*                       pParamKey
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_DEL_OBJECT)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pObjectName,
        char*                       pParamKey
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_DOWNLOAD)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hDownloadReq
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_REBOOT)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pCommandKey
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_GET_Q_TRANS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_SCHEDULE_IN)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ULONG                       ulDelaySeconds,
        char*                       pCommandKey
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_SET_VOUCHER)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pVoucherList
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_GET_OPTIONS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pOptionName
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_UPLOAD)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hUploadReq
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_FACTORY_RES)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

typedef  ANSC_STATUS
(*PFN_DSLHMCOIF_CHANGE_DU_STATE)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hCdsReq
    );

/*
 * In each direction, the order of SOAP envelopes is defined independently from the number of enve-
 * lopes per HTTP post/response pair. Specifically, envelopes are ordered from first to last within
 * a single HTTP post/response and then between successive post/response pairs.
 *
 * On reception of SOAP requests from the ACS, the CPE MUST respond to each request in the order
 * they were received, where order is defined as described above. The definition of order places no
 * constraint on whether multiple responses are sent in a single HTTP post (if the ACS can accept
 * more than one envelope), or distributed over multiple HTTP posts.
 */
#define  DSLH_MCO_INTERFACE_CLASS_CONTENT                                                   \
    /* duplication of the base object class content */                                      \
    ANSCIFO_CLASS_CONTENT                                                                   \
    /* start of object class content */                                                     \
    PFN_DSLHMCOIF_REGISTER          RegDeferredAction;                                      \
    PFN_DSLHMCOIF_NOTIFY            NotifyAcsStatus;                                        \
    PFN_DSLHMCOIF_GET_TYPE          GetNextMethod;                                          \
    PFN_DSLHMCOIF_PROCESS           ProcessSoapResponse;                                    \
    PFN_DSLHMCOIF_PROCESS2          ProcessSoapError;                                       \
    PFN_DSLHMCOIF_INVOKE            InvokeUnknownMethod;                                    \
                                                                                            \
    PFN_DSLHMCOIF_GET_METHODS       GetRpcMethods;                                          \
    PFN_DSLHMCOIF_SET_PARAM_V       SetParameterValues;                                     \
    PFN_DSLHMCOIF_GET_PARAM_V       GetParameterValues;                                     \
    PFN_DSLHMCOIF_GET_PARAM_N       GetParameterNames;                                      \
    PFN_DSLHMCOIF_SET_PARAM_A       SetParameterAttributes;                                 \
    PFN_DSLHMCOIF_GET_PARAM_A       GetParameterAttributes;                                 \
    PFN_DSLHMCOIF_ADD_OBJECT        AddObject;                                              \
    PFN_DSLHMCOIF_DEL_OBJECT        DeleteObject;                                           \
    PFN_DSLHMCOIF_DOWNLOAD          Download;                                               \
    PFN_DSLHMCOIF_REBOOT            Reboot;                                                 \
                                                                                            \
    PFN_DSLHMCOIF_CHANGE_DU_STATE   ChangeDUState;                                          \
                                                                                            \
    PFN_DSLHMCOIF_GET_Q_TRANS       GetQueuedTransfers;                                     \
    PFN_DSLHMCOIF_SCHEDULE_IN       ScheduleInform;                                         \
    PFN_DSLHMCOIF_SET_VOUCHER       SetVouchers;                                            \
    PFN_DSLHMCOIF_GET_OPTIONS       GetOptions;                                             \
    PFN_DSLHMCOIF_UPLOAD            Upload;                                                 \
    PFN_DSLHMCOIF_FACTORY_RES       FactoryReset;                                           \
    /* end of object class content */                                                       \

typedef  struct
_DSLH_MCO_INTERFACE
{
    DSLH_MCO_INTERFACE_CLASS_CONTENT
}
DSLH_MCO_INTERFACE,  *PDSLH_MCO_INTERFACE;

#define  ACCESS_DSLH_MCO_INTERFACE(p)               \
         ACCESS_CONTAINER(p, DSLH_MCO_INTERFACE, Linkage)


/***********************************************************
   DSLH MANAGEMENT CLIENT OPERATION PARAMETERS DEFINITION
***********************************************************/

/*
 * the Download() method may be used by the Server to cause the CPE to download a specified file
 * from the designated location. The following data structure encapsulates the calling arguments
 * for this method.
 */
typedef  struct
_DSLH_MCO_DOWNLOAD_REQ
{
    char*                           CommandKey;
    char*                           FileType;
    char*                           Url;
    char*                           Username;
    char*                           Password;
    ULONG                           FileSize;
    char*                           TargetFileName;
    ULONG                           DelaySeconds;
    char*                           SuccessUrl;
    char*                           FailureUrl;
}
DSLH_MCO_DOWNLOAD_REQ,  *PDSLH_MCO_DOWNLOAD_REQ;

#define  DslhMcoCleanDownloadReq(download_req)                                              \
         {                                                                                  \
            if ( download_req->CommandKey )                                                 \
            {                                                                               \
                AnscFreeMemory(download_req->CommandKey);                                   \
                                                                                            \
                download_req->CommandKey = NULL;                                            \
            }                                                                               \
                                                                                            \
            if ( download_req->FileType )                                                   \
            {                                                                               \
                AnscFreeMemory(download_req->FileType);                                     \
                                                                                            \
                download_req->FileType = NULL;                                              \
            }                                                                               \
                                                                                            \
            if ( download_req->Url )                                                        \
            {                                                                               \
                AnscFreeMemory(download_req->Url);                                          \
                                                                                            \
                download_req->Url = NULL;                                                   \
            }                                                                               \
                                                                                            \
            if ( download_req->Username )                                                   \
            {                                                                               \
                AnscFreeMemory(download_req->Username);                                     \
                                                                                            \
                download_req->Username = NULL;                                              \
            }                                                                               \
                                                                                            \
            if ( download_req->Password )                                                   \
            {                                                                               \
                AnscFreeMemory(download_req->Password);                                     \
                                                                                            \
                download_req->Password = NULL;                                              \
            }                                                                               \
                                                                                            \
            if ( download_req->TargetFileName )                                             \
            {                                                                               \
                AnscFreeMemory(download_req->TargetFileName);                               \
                                                                                            \
                download_req->TargetFileName = NULL;                                        \
            }                                                                               \
                                                                                            \
            if ( download_req->SuccessUrl )                                                 \
            {                                                                               \
                AnscFreeMemory(download_req->SuccessUrl);                                   \
                                                                                            \
                download_req->SuccessUrl = NULL;                                            \
            }                                                                               \
                                                                                            \
            if ( download_req->FailureUrl )                                                 \
            {                                                                               \
                AnscFreeMemory(download_req->FailureUrl);                                   \
                                                                                            \
                download_req->FailureUrl = NULL;                                            \
            }                                                                               \
         }

#define  DslhMcoFreeDownloadReq(download_req)                                               \
         {                                                                                  \
            DslhMcoCleanDownloadReq(download_req);                                          \
            AnscFreeMemory         (download_req);                                          \
         }

/*
 * The Upload() method may be used by the Server to cause the CPE to upload a specified file to the
 * designated location. The support for this method is optional. The following data structure encap-
 * sulates the calling arguments for this method.
 */
typedef  struct
_DSLH_MCO_UPLOAD_REQ
{
    char*                           CommandKey;
    char*                           FileType;
    char*                           Url;
    char*                           Username;
    char*                           Password;
    ULONG                           DelaySeconds;
}
DSLH_MCO_UPLOAD_REQ,  *PDSLH_MCO_UPLOAD_REQ;

#define  DslhMcoCleanUploadReq(upload_req)                                                  \
         {                                                                                  \
            if ( upload_req->CommandKey )                                                   \
            {                                                                               \
                AnscFreeMemory(upload_req->CommandKey);                                     \
                                                                                            \
                upload_req->CommandKey = NULL;                                              \
            }                                                                               \
                                                                                            \
            if ( upload_req->FileType )                                                     \
            {                                                                               \
                AnscFreeMemory(upload_req->FileType);                                       \
                                                                                            \
                upload_req->FileType = NULL;                                                \
            }                                                                               \
                                                                                            \
            if ( upload_req->Url )                                                          \
            {                                                                               \
                AnscFreeMemory(upload_req->Url);                                            \
                                                                                            \
                upload_req->Url = NULL;                                                     \
            }                                                                               \
                                                                                            \
            if ( upload_req->Username )                                                     \
            {                                                                               \
                AnscFreeMemory(upload_req->Username);                                       \
                                                                                            \
                upload_req->Username = NULL;                                                \
            }                                                                               \
                                                                                            \
            if ( upload_req->Password )                                                     \
            {                                                                               \
                AnscFreeMemory(upload_req->Password);                                       \
                                                                                            \
                upload_req->Password = NULL;                                                \
            }                                                                               \
         }

#define  DslhMcoFreeUploadReq(upload_req)                                                   \
         {                                                                                  \
            DslhMcoCleanUploadReq(upload_req);                                              \
            AnscFreeMemory       (upload_req);                                              \
         }


/*
 * The ChangeDUState() method may be used by the Server to cause the CPE to perform
 * software module management operations.
 */

typedef  struct
_DSLH_MCO_CDS_REQ
{
    char*                           CommandKey;
    char*                           Operations;
}
DSLH_MCO_CDS_REQ,  *PDSLH_MCO_CDS_REQ;

#define  DslhMcoCleanCdsReq(cds_req)                                                        \
         {                                                                                  \
            if ( cds_req->CommandKey )                                                      \
            {                                                                               \
                AnscFreeMemory(cds_req->CommandKey);                                        \
                                                                                            \
                cds_req->CommandKey = NULL;                                                 \
            }                                                                               \
                                                                                            \
            if ( cds_req->Operations )                                                      \
            {                                                                               \
                AnscFreeMemory(cds_req->Operations);                                        \
                                                                                            \
                cds_req->Operations = NULL;                                                 \
            }                                                                               \
         }




#endif
