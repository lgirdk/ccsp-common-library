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

    module:	kernel_string.h

        For Advanced Networking Service Container (ANSC),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco System  , Inc., 1997 ~ 2001
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This wrapper file defines some basic data types and
        structures on a particular platform.

    ---------------------------------------------------------------

    environment:

        atmos 7.1   and later

    ---------------------------------------------------------------

    author:

        Xuechen Yang
        Hua Ding

    ---------------------------------------------------------------

    revision:

        01/19/01    initial revision.
        04/24/02    atmos port

**********************************************************************/


#ifndef  _KERNEL_STRING_
#define  _KERNEL_STRING_


/***********************************************************
        DEFINITION OF BASIC DATA TYPE AND STRUCTURES
***********************************************************/


/***********************************************************
       BASIC OPERATIONS BY MACROS AND INLINE FUNCTIONS
***********************************************************/

/*
 *  prototype
 *
ULONG
KernelSizeOfString
    (
        char*                       pStr
    );
 */
#define  KernelSizeOfString(s)                      (ULONG)(strlen(s))


/*
 *  prototype
 *
ULONG
KernelCatString
    (
        char*                       pDestStr,
        char*                       pSrcStr
    );
 */
#define  KernelCatString(pDestStr, pSrcStr)         strcat(pDestStr, pSrcStr)


/*
 *  prototype
 *
BOOLEAN
KernelEqualString1
    (
        char*                       pString1,
        char*                       pString2,
        BOOL                        bCaseSensitive
    );
 */
#define  KernelEqualString1(pStr1, pStr2, bCs)      (bCs ? (strcmp(pStr1, pStr2)  == 0) : (stricmp(pStr1, pStr2) == 0))


BOOLEAN
KernelEqualString2
    (
        char*                       pString1,
        char*                       pString2,
        ULONG                       length,
        BOOL                        bCaseSensitive
    );


/*
 *  prototype
 *
VOID
KernelCopyString
    (
        char*                       destination,
        char*                       source
    );
 */
#define  KernelCopyString(destination, source)      strcpy(destination, source)


/*
 *  prototype
 *
BOOLEAN
KernelCharInString
    (
        char*                       pString,
        char                        charToFind
    );
 */
#define  KernelCharInString(pString, charToFind)    (strchr(pString, charToFind) ? TRUE : FALSE)


#endif
