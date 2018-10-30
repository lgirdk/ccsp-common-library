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

    module:	user_string.h

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

        platform dependent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        01/19/01    initial revision.

**********************************************************************/


#ifndef  _USER_STRING_
#define  _USER_STRING_


/***********************************************************
        DEFINITION OF BASIC DATA TYPE AND STRUCTURES
***********************************************************/


/***********************************************************
       BASIC OPERATIONS BY MACROS AND INLINE FUNCTIONS
***********************************************************/

#define  UserSizeOfString(s)                        (ULONG)(strlen(s))
#define  UserCatString                              strcat

__inline  BOOLEAN
UserEqualString1(char*  pString1, char*  pString2, BOOL  bCaseSensitive)
{
    ULONG       ulStringSize1 = pString1? UserSizeOfString(pString1) : 0;
    ULONG       ulStringSize2 = pString2? UserSizeOfString(pString2) : 0;
    ULONG       i             = 0;

    if ( !pString1 && !pString2 )
    {
        return  TRUE;
    }
    else if ( !pString1 || !pString2 )
    {
        return  FALSE;
    }
    else if ( ulStringSize1 != ulStringSize2 )
    {
        return  FALSE;
    }

    for ( i = 0; i < (ULONG)ulStringSize1; i++ )
    {
        if ( pString1[i] != pString2[i] )
        {
            if ( bCaseSensitive )
            {
                return  FALSE;
            }

            if ( pString1[i] >= 'a' && pString1[i] <= 'z' )
            {
                if ( pString2[i] < 'A' || pString2[i] > 'Z' )
                {
                    return  FALSE;
                }
                else if ( (pString1[i] - 'a') != (pString2[i] - 'A') )
                {
                    return  FALSE;
                }
            }
            else if ( pString1[i] >= 'A' && pString1[i] <= 'Z' )
            {
                if ( pString2[i] < 'a' || pString2[i] > 'z' )
                {
                    return  FALSE;
                }
                else if ( (pString1[i] - 'A') != (pString2[i] - 'a') )
                {
                    return  FALSE;
                }
            }
            else
            {
                return  FALSE;
            }
        }
    }

    return  TRUE;
}

__inline  BOOLEAN
UserEqualString2(char*  pString1, char*  pString2, ULONG  length, BOOL  bCaseSensitive)
{
    ULONG       i = 0;

    if ( !pString1 && !pString2 )
    {
        return  TRUE;
    }
    if ( !pString1 || !pString2 )
    {
        return  FALSE;
    }

    for ( i = 0; i < length; i++ )
    {
        if ( pString1[i] != pString2[i] )
        {
            if ( bCaseSensitive )
            {
                return  FALSE;
            }

            if ( pString1[i] >= 'a' && pString1[i] <= 'z' )
            {
                if ( pString2[i] < 'A' || pString2[i] > 'Z' )
                {
                    return  FALSE;
                }
                else if ( (pString1[i] - 'a') != (pString2[i] - 'A') )
                {
                    return  FALSE;
                }
            }
            else if ( pString1[i] >= 'A' && pString1[i] <= 'Z' )
            {
                if ( pString2[i] < 'a' || pString2[i] > 'z' )
                {
                    return  FALSE;
                }
                else if ( (pString1[i] - 'A') != (pString2[i] - 'a') )
                {
                    return  FALSE;
                }
            }
            else
            {
                return  FALSE;
            }
        }
    }

    return  TRUE;
}

__inline  void
UserCopyString(char*  destination, char*  source)
{
    if ( !source )
    {
        destination[0] = 0;
    }
    else
    {
        strcpy(destination, source);
    }

    return;
}

__inline  BOOLEAN
UserCharInString(char*  pString, char  charToFind)
{
    if ( !strchr(pString, charToFind) )
    {
        return  FALSE;
    }

    return  TRUE;
}


#endif
