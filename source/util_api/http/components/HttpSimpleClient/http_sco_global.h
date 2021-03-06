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

    module:	http_sco_global.h

        For HyperText Transfer Protocol Implementation (HTTP),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This header file includes all the header files required by
        the Http Simple Client implementation.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        04/21/02    initial revision.

**********************************************************************/


#ifndef  _HTTP_SCO_GLOBAL_
#define  _HTTP_SCO_GLOBAL_


#include "ansc_platform.h"
#include "ansc_socket.h"
#include "ansc_socket_external_api.h"
#include "ansc_scto_interface.h"
#include "ansc_scto_external_api.h"
#include "ansc_tso_interface.h"
#include "ansc_tso_external_api.h"

#include "ansc_crypto_interface.h"
#include "ansc_crypto_external_api.h"

#include "http_co_oid.h"
#include "http_co_name.h"
#include "http_co_type.h"
#include "http_properties.h"

#include "http_ifo_wsp.h"
#include "http_ifo_hfp.h"

#include "http_sco_interface.h"
#include "http_sco_exported_api.h"
#include "http_sco_internal_api.h"
#include "http_ifo_cas.h"

#include "http_authco_interface.h"
#include "http_authco_exported_api.h"

#include "http_wcso_interface.h"
#include "http_wcso_exported_api.h"
#include "http_wcto_interface.h"
#include "http_wcto_exported_api.h"

#include "http_bmo_interface.h"
#include "http_bmo_exported_api.h"
#include "http_bmoreq_interface.h"
#include "http_bmoreq_exported_api.h"
#include "http_bmorep_interface.h"
#include "http_bmorep_exported_api.h"


#endif
