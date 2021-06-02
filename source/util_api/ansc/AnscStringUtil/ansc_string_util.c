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


#include "ansc_platform.h"
#include "ansc_string_util.h"


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        AnscStrBufGetCharNum
            (
                PUCHAR                      pString,
                ULONG                       ulStrLen,
                UCHAR                       uChar
            )

    description:

        This function is called to count the specified character
        in the given string.

    argument:   PUCHAR                      pString
                The string to be processed.

                ULONG                       ulStrLen
                The length of string.

                UCHAR                       uChar
                The character to be counted.

    return:     the number of characters in the string.

**********************************************************************/

ULONG
AnscStrBufGetCharNum
    (
        PUCHAR                      pString,
        ULONG                       ulStrLen,
        UCHAR                       uChar
    )
{
    ULONG                           i;
    ULONG                           ulCount = 0;
    PUCHAR                          pBuf;

    if (pString && ulStrLen != 0)
    {
        pBuf    = pString;
        for (i = 0; i < ulStrLen; i ++)
        {
            if (*pBuf == uChar)
                ulCount ++;

            pBuf ++;
        }
    }

    return ulCount;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        AnscStrGetCharNum
            (
                PUCHAR                      pString,
                UCHAR                       uChar
            )

    description:

        This function is called to get specific character
        in given string.

    argument:   PUCHAR                      pString
                The string to be processed.

                UCHAR                       uChar
                The character to be counted.

    return:     the number of characters in the string.

**********************************************************************/

ULONG
AnscStrGetCharNum
    (
        PUCHAR                      pString,
        UCHAR                       uChar
    )
{
    ULONG                           ulCount = 0;

    if (pString)
    {
        ULONG                       ulStrLen;

        ulStrLen    = AnscSizeOfString((const char *)pString);

        ulCount     = AnscStrBufGetCharNum(pString, ulStrLen, uChar);
    }

    return ulCount;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        PUCHAR
        AnscStrUpper
            (
                PUCHAR                      pStr
            )

    description:

        This function is called to captilize the given string.

    argument:   PUCHAR                      pStr
                The string to be processed.

    return:     the uppercase string.

**********************************************************************/

PUCHAR
AnscStrUpper
    (
        PUCHAR                      pStr
    )
{
    ULONG                           i, ulStrLen;
    UCHAR                           ch;

    ulStrLen    = AnscSizeOfString((const char *)pStr);

    for (i = 0; i < ulStrLen; i ++)
    {
        ch  = pStr[i];

        if (ch >= 'a' && ch <= 'z')
            pStr[i] = ch - 'a' + 'A';
    }

    return pStr;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        AnscStrLower
            (
                PUCHAR                      pStr
            )

    description:

        This function is called to convert all letters to
        lower case.

    argument:   PUCHAR                      pStr
                The string to be processed.

    return:     the string with all letters in lower case.

**********************************************************************/

PUCHAR
AnscStrLower
    (
        PUCHAR                      pStr
    )
{
    ULONG                           i, ulStrLen;
    UCHAR                           ch;

    ulStrLen    = AnscSizeOfString((const char *)pStr);

    for (i = 0; i < ulStrLen; i ++)
    {
        ch  = pStr[i];

        if (ch >= 'A' && ch <= 'Z')
            pStr[i] = ch - 'A' + 'a';
    }

    return pStr;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        AnscDupString
            (
                PUCHAR                      pStr
            )

    description:

        This function is called to duplicate the given string.

    argument:   PUCHAR                      pStr
                The string to be duplicated.

    return:     the copy of the given string.

**********************************************************************/

PUCHAR
AnscDupString
    (
        PUCHAR                      pStr
    )
{
    if (!pStr)
    {
        return NULL;
    }
    else
    {
        ULONG                       ulStrLen;
        PUCHAR                      pDupStr;

        ulStrLen    = AnscSizeOfString((const char *)pStr);

        pDupStr     = (PUCHAR)AnscAllocateMemory(ulStrLen + 1);
        if (ulStrLen != 0)
            AnscCopyString((char *)pDupStr, (char *)pStr);
        else
            pDupStr[0]  = 0;

        return pDupStr;
    }
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        PUCHAR
        AnscDupString2
            (
                PUCHAR                      pStr,
                ULONG                       ulStrLen,
                ULONG                       ulNumPadding
            );

    description:

        This function is called to duplicate the given string.

    argument:   PUCHAR                      pStr
                The string to be duplicated.

                ULONG                       ulStrLen
                Length to string to be copied.

                ULONG                       ulNumPadding
                The number of padding in bytes at the end of
                the new string and must be zeroed out.

    return:     the copy of the given string.

**********************************************************************/

PUCHAR
AnscDupString2
    (
        PUCHAR                      pStr,
        ULONG                       ulStrLen,
        ULONG                       ulNumPadding
    )
{
    if (!pStr)
    {
        return NULL;
    }
    else
    {
        PUCHAR                      pDupStr;
        ULONG                       i;

        pDupStr     = (PUCHAR)AnscAllocateMemory(ulStrLen + 1 + ulNumPadding);

        if (ulStrLen != 0)
        {
            AnscCopyMemory(pDupStr, pStr, ulStrLen);
        }
        else
        {
            pDupStr[0]  = 0;
        }

        for (i = 0; i <= ulNumPadding; i ++)
        {
            pDupStr[i + ulStrLen]    = 0;
        }

        return pDupStr;
    }
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        AnscDupIp4Addr
            (
                PUCHAR                      pStr
            )

    description:

        This function is called to duplicate a string that
        represent an IP address.

    argument:   PUCHAR                      pStr
                The IP address string to be duplicated.

    return:     the copy of IP address string.

**********************************************************************/

PUCHAR
AnscDupIp4Addr
    (
        PUCHAR                      pStr
    )
{
    /* this function generate string format of a IP4 address */
    if (!pStr)
    {
        return NULL;
    }
    else
    {
        ULONG                       ulStrLen;
        PUCHAR                      pDupStr;

        /* xxx.xxx.xxx.xxx */
        ulStrLen    = 15;

        pDupStr     = (PUCHAR)AnscAllocateMemory(ulStrLen + 1);

        if (pDupStr)
        {
            _ansc_sprintf((char *)pDupStr, "%d.%d.%d.%d", pStr[0], pStr[1], pStr[2], pStr[3]);
        }

        return pDupStr;
    }
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        AnscDupMacAddr
            (
                PUCHAR                      pStr
            )

    description:

        This function is called to duplicate MAC address string.

    argument:   PUCHAR                      pStr
                The MAC address string.

    return:     the copy MAC address string.

**********************************************************************/

PUCHAR
AnscDupMacAddr
    (
        PUCHAR                      pStr
    )
{
    /* this function generate string format of a IP4 address */
    if (!pStr)
    {
        return NULL;
    }
    else
    {
        ULONG                       ulStrLen;
        PUCHAR                      pDupStr;

        /* xx-xx-xx-xx-xx-xx */
        ulStrLen    = 3 * ANSC_MAX_MAC_ADDRESS_SIZE;

        pDupStr     = (PUCHAR)AnscAllocateMemory(ulStrLen);

        if (pDupStr)
        {
            _ansc_sprintf
                (
                    (char *)pDupStr, 
                    "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", 
                    pStr[0], 
                    pStr[1], 
                    pStr[2], 
                    pStr[3],
                    pStr[4],
                    pStr[5]
                );
        }

        return pDupStr;
    }
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        void
        AnscStr2Ip4Addr
            (
                PUCHAR                      pStr,
                PUCHAR                      pIp4Addr
            )

    description:

        This function is called to convert a string to IP address.

    argument:   PUCHAR                      pStr
                The string to be processed.

                PUCHAR                      pIp4Addr
                The buffer for IP address.

    return:     void.

**********************************************************************/

void
AnscStr2Ip4Addr
    (
        PUCHAR                      pStr,
        PUCHAR                      pIp4Addr
    )
{
    if (pStr && pIp4Addr)
    {
        /* we don't valid the format of string format IP4 address */

        *(PULONG)pIp4Addr   = _ansc_inet_addr((char *)pStr);
    }
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        PVOID
        AnscMemUtilRealloc
            (
                PUCHAR                      pMem,
                ULONG                       ulSize,
                ULONG                       ulNewSize
            )

    description:

        This function is called to reallocate memory.

    argument:   PUCHAR                      pMem
                The memory needs to be reallocated.

                ULONG                       ulSize
                The old size of memory.

                ULONG                       ulNewSize
                The new memory size.

    return:     the new memory block.

**********************************************************************/

PVOID
AnscMemUtilRealloc
    (
        PVOID                       pMem,
        ULONG                       ulSize,
        ULONG                       ulNewSize
    )
{
    PVOID                           pNewMem;
    ULONG                           ulCopySize;

    if (ulNewSize == 0)
    {
        if (pMem)
        {
            AnscFreeMemory(pMem);
        }

        return NULL;
    }

    pNewMem = AnscAllocateMemory(ulNewSize);

    if (ulSize == 0 || !pMem)
    {
        return pNewMem;
    }

    if (pNewMem)
    {
        /* copy content from pMem to pNewMem */
        ulCopySize  = (ulNewSize > ulSize)?ulSize:ulNewSize;

        AnscCopyMemory(pNewMem, pMem, ulCopySize);

        /* free old memory block */
        AnscFreeMemory(pMem);
    }

    return pNewMem;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        PUCHAR
        DslhTcpcrhoMemSearch
            (
                PUCHAR                      pBuf,
                ULONG                       ulSize,
                PUCHAR                      pPattern,
                ULONG                       ulPatternLen,
                BOOL                        bCaseSensitive
            );

    description:

        This function is called to find specific 'string'
        pattern in given memory buffer.

    argument:   PUCHAR                      pBuf
                Memory to be searched.

                ULONG                       ulSize
                The size of memory buffer.

                PUCHAR                      pPattern
                The search pattern.

                ULONG                       ulPatternLen
                Size of pattern string.

                BOOL                        bCaseSensitive
                Sensitiveness of string comparison.

    return:     the number of characters in the string.

**********************************************************************/

PUCHAR
AnscMemorySearch
    (
        PUCHAR                      pBuf,
        ULONG                       ulSize,
        PUCHAR                      pPattern,
        ULONG                       ulPatternLen,
        BOOL                        bCaseSensitive
    )
{
    PUCHAR                          pBufEnd     = pBuf + ulSize - 1;
    PUCHAR                          pNext, pNext1;
    UCHAR                           fc          = *pPattern;
    UCHAR                           fc1         = 0;

    if ( fc >= 'a' && fc <= 'z')
    {
        fc1 = fc - 'a' + 'A';
    }
    else if ( fc >= 'A' && fc <= 'Z' )
    {
        fc1 = fc - 'A' + 'a';
    }

    pNext1 = NULL;

    while ( pBuf && pBuf <= pBufEnd )
    {
        pNext = _ansc_memchr(pBuf, fc, pBufEnd - pBuf + 1);
        if ( fc1 != 0 )
        {
            pNext1 = _ansc_memchr(pBuf, fc, pBufEnd - pBuf + 1);
        }

        if ( !pNext )
        {
            pNext = pNext1;
        }
        else if ( pNext1 && pNext1 < pNext )
        {
            pNext = pNext1;
        }

        if ( !pNext )
        {
            return  NULL;
        }

        if ( pBufEnd - pNext + 1 >= (int)ulPatternLen &&
             AnscEqualString2((char *)pNext, (char *)pPattern, ulPatternLen, bCaseSensitive) )
        {
            return  pNext;
        }

        pBuf = pNext + 1;
    }

    return  NULL;
}

BOOL
is_IpAddress
    (
        PUCHAR                      pString
    )
{
    struct sockaddr_in sa;
    if(inet_pton(AF_INET, (const char *)pString, &(sa.sin_addr))==1)
        return TRUE;
    else
        return FALSE;
}

BOOL
is_Ipv6_address
    (
        PUCHAR                      pString
    )
{
    struct sockaddr_in6 sa;
    if(inet_pton(AF_INET6, (const char *)pString, &(sa.sin6_addr))==1)
        return TRUE;
    else
        return FALSE;
}

BOOL
AnscValidStringCheck
    (
        PUCHAR                      pString
    )
{
    int i =0;
    
    /* check if pstring doesn't hold NULL or whitespaces */
    if((pString == NULL) || (*pString=='\0'))
    {
        return FALSE;
    }
    while(pString[i] != '\0')
    {
        if ((pString[i] == ' ') || (pString[i] == '<') || (pString[i] == '>') || (pString[i] == '&') || (pString[i] == '\'') || (pString[i] == '\"') || (pString[i] == '|'))
        {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}
