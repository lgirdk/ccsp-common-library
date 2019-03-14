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

    module:	tls_aco_interface.h

        For Transport Layer Security Implementation (TLS),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for the TLS App Connector Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        05/26/03    initial revision.

**********************************************************************/


#ifndef  _TLS_ACO_INTERFACE_
#define  _TLS_ACO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "tls_rco_interface.h"
#include "tls_rco_exported_api.h"
#include "tls_properties.h"


/***********************************************************
    PLATFORM INDEPENDENT APP CONNECTOR OBJECT DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the object mapper object definition.
 */

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */

/*
 * Application data messages are carried by the Record Layer and are fragmented, compressed and
 * encrypted based on the current connection state. The messages are treated as transparent data to
 * the record layer.
 */
#define  TLS_APP_CONNECTOR_CLASS_CONTENT                                                    \
    /* duplication of the base object class content */                                      \
    TLS_RECORD_CLIENT_CLASS_CONTENT                                                         \
    /* start of object class content */                                                     \
    /* end of object class content */                                                       \

typedef  struct
_TLS_APP_CONNECTOR_OBJECT
{
    TLS_APP_CONNECTOR_CLASS_CONTENT
}
TLS_APP_CONNECTOR_OBJECT,  *PTLS_APP_CONNECTOR_OBJECT;

#define  ACCESS_TLS_APP_CONNECTOR_OBJECT(p)         \
         ACCESS_CONTAINER(p, TLS_APP_CONNECTOR_OBJECT, Linkage)


#endif
