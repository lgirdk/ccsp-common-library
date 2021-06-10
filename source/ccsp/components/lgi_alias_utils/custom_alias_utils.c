#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ansc_platform.h"

//=============================================================================

#include "custom_alias_utils.h"

typedef struct Alias_t
{
    char* name;
    char* aliasName[MAX_ALIAS];
    unsigned char aliasCount;
    unsigned char aliasStrict;
}Alias_t;

// gperf utility
extern struct Alias_t* map_ExternalToInternal(const char* str, unsigned int len);
extern struct Alias_t* map_InternalToExternal(const char* str, unsigned int len);

#define INSTANCE_ID_ON_MAPPER "{i}"
#define INSTANCE_ID_MAX 10
#define BUF_SIZE 256

//=============================================================================

static int convertInstaceIDForMapping(char* inStr, char* outStr, int indexIds[], int* indexIdCount)
{
    int index = 0;
    int i = 0;
    char* in = inStr;
    char* out = outStr;

    while (*in)
    {
        if (strstr(in, ".") == in)
        {
            out[i++] = *in++;
            if (*in)
            {
                if ((index < INSTANCE_ID_MAX) && (isdigit(*in)))
                {
                    sprintf(&out[i], "%s", INSTANCE_ID_ON_MAPPER);
                    long val = strtol(in, &in, 10);
                    indexIds[index] = (int)val;
                    i += 3;  // 3 - size of "{i}"
                    index++;
                }
                else
                {
                    out[i++] = *in++;
                }
            }
        }
        else
        {
            out[i++] = *in++;
        }
    }
    out[i] = '\0';
    *indexIdCount = index;
    return 0;
}

//=============================================================================

static int restoreInstaceIDAfterMapping(char* inStr, char* outStr, int indexIds[], int indexIdCount)
{
    int index = 0;
    int i = 0;
    char* in = inStr;
    char* out = outStr;

    while (*in)
    {
        if (strstr(in, ".") == in)
        {
            out[i++] = *in++;
            if (*in)
            {
                if ((index < indexIdCount) && (strstr(in, INSTANCE_ID_ON_MAPPER) == in))
                {
                    int val = indexIds[index];
                    sprintf(&out[i], "%d", val);
                    do
                    {
                        i++;
                        val /= 10;
                    } while (val != 0);
                    in += 3;  // 3 - size of "{i}";
                    index++;
                }
                else
                {
                    out[i++] = *in++;
                }
            }
        }
        else
        {
            out[i++] = *in++;
        }
    }
    out[i] = '\0';
    return 0;
}

//=============================================================================

static const char* getAliasName(char* inName, unsigned char aliasType, unsigned char useDynamicMem, int* pReleaseMem)
{
    const char* retVal = NULL;
    struct Alias_t* pStAlias;
    int indexIds[10];
    int indexIdCount;
    char temp_buf[BUF_SIZE];
    char* pMapStr;
    int releaseMem = 0;

    if ((NULL == inName) || !strcmp(inName, "Device.")) return NULL;

    convertInstaceIDForMapping(inName, temp_buf, indexIds, &indexIdCount);

    // Assumption: Input DM parameter name always starts with "Device.", so it is ignored during mapping
    pMapStr = temp_buf + 7;
    if (0 == aliasType)
        // Get Internal name (External -> Internal)
        pStAlias = map_ExternalToInternal(pMapStr, strlen(pMapStr));
    else
        // Get External name (Internal -> External)
        pStAlias = map_InternalToExternal(pMapStr, strlen(pMapStr));

    if ((NULL != pStAlias) && (pStAlias->aliasCount != 0))
    {
        if (indexIdCount != 0)
        {
             restoreInstaceIDAfterMapping(pStAlias->aliasName[0], temp_buf, indexIds, indexIdCount);
             retVal = AnscCloneString(temp_buf);
             releaseMem = 1;
        }
        else 
        {
            if (useDynamicMem)
            {
                retVal = AnscCloneString(pStAlias->aliasName[0]);
                releaseMem = 1;
            }
            else
            {
                retVal = pStAlias->aliasName[0];
            }
        }
        if (pReleaseMem) 
            *pReleaseMem = releaseMem;
        //fprintf(stderr, "%s: %s->%s\n", __FUNCTION__, inName, retVal);
    }
    return retVal;
}

//=============================================================================

// aliasGetInternalName: Depending on the flag "pReleaseMem", caller function release memory used for returned string 
const char* aliasGetInternalName(char* externalName, int* pReleaseMem)
{
    return getAliasName(externalName, 0, 0, pReleaseMem);
}

//=============================================================================

// aliasGetExternalName: Depending on the flag "pReleaseMem", caller function release memory used for returned string 
const char* aliasGetExternalName(char* internalName, int* pReleaseMem)
{
    return getAliasName(internalName, 1, 0, pReleaseMem);
}

//=============================================================================

// lgiAliasGetInternalName: Caller function always releases memory used for returned string 
const char* lgiAliasGetInternalName(char* externalName)
{
    return getAliasName(externalName, 0, 1, NULL);
}

//=============================================================================

// lgiAliasGetExternalName: Caller function always releases memory used for returned string 
const char* lgiAliasGetExternalName(char* internalName)
{
    return getAliasName(internalName, 1, 1, NULL);
}

//=============================================================================

aliasNames_t* lgiAliasGetInternalNames(char* externalName)
{
    struct aliasNames_t* pAliasNames = NULL;
    struct Alias_t* pStAlias = NULL;
    int i;
    int indexIds[10];
    int indexIdCount;
    char temp_buf[BUF_SIZE];
    char* pMapStr;

    if ((NULL == externalName) || !strcmp(externalName, "Device.")) return NULL;
    convertInstaceIDForMapping(externalName, temp_buf, indexIds, &indexIdCount);

    // Assumption: Input DM parameter name always starts with "Device.", so it is ignored during mapping
    pMapStr = temp_buf + 7;
    pStAlias = map_ExternalToInternal(pMapStr, strlen(pMapStr));
    if ((NULL != pStAlias) && (pStAlias->aliasCount != 0))
    {
        pAliasNames = (aliasNames_t*) AnscAllocateMemory(sizeof(struct aliasNames_t));
        pAliasNames->aliasCount = 0;
        for (i = 0; i < MAX_ALIAS; i++)
            pAliasNames->aliasName[i] = 0;
        if (indexIdCount == 0)
        {
            for (i = 0; i < pStAlias->aliasCount; i++)
            {
                pAliasNames->aliasName[i] = AnscCloneString (pStAlias->aliasName[i]);
                pAliasNames->aliasCount++;
//                fprintf(stderr, "%s: %s, aliasName[%d]=%s\n", __FUNCTION__, externalName, i, pAliasNames->aliasName[i]);
            }
        }
        else
        {
            // Can have only one name in the list
            restoreInstaceIDAfterMapping(pStAlias->aliasName[0], temp_buf, indexIds, indexIdCount);
            pAliasNames->aliasName[0] = AnscCloneString (temp_buf);
            pAliasNames->aliasCount++;
//            fprintf(stderr, "%s: %s, aliasName[0]=%s\n", __FUNCTION__, externalName, pAliasNames->aliasName[0]);
        }
    }
    return pAliasNames;
}

//=============================================================================

const char* lgiAliasGetNextName(struct aliasNames_t* pAliasNames)
{
    const char* retVal = NULL;
    int i;
    if (NULL == pAliasNames) return NULL;
    if (0 == pAliasNames->aliasCount) return NULL;

    for (i = 0; i < MAX_ALIAS; i++)
    {
        if (NULL != pAliasNames->aliasName[i])
        {
            retVal = pAliasNames->aliasName[i];
            pAliasNames->aliasName[i] = 0;
            pAliasNames->aliasCount--;
            break;
        }
    }
    return retVal;
}

//=============================================================================

void lgiAliasFreeNamesList(struct aliasNames_t* pAliasNames)
{
    int i;
    if (NULL == pAliasNames) return;

    for (i = 0; i < MAX_ALIAS; i++)
    {
        if (NULL != pAliasNames->aliasName[i])
        {
            AnscFreeMemory(pAliasNames->aliasName[i]);
        }
    }
    AnscFreeMemory(pAliasNames);
}

//=============================================================================

#if 0
int main(int argc, char* argv[])
{
#if 0 
    // For reference
    Device.X_CISCO_COM_GRE.Interface.1.Mode
    Device.X_CISCO_COM_GRE.Interface.2.
    Device.X_CISCO_COM_GRE.Interface.
    Device.X_CISCO_COM_GRE.
#endif
    const char* retVal;
    int releaseMem;

    printf("\t *** Alias custom mapper utility ***\n");
    if (argc != 3)
    {
        printf("Error: Invalid argument...\n\n");
        printf("Usage:custom_alias_utils <int>/<ext> <parameter> \n");
        printf("\te.g: custom_alias_utils int Device.X_RDKCENTRAL-COM_GRE.Interface.1.Mode\n\n");
        return -1;
    }

    if ((strcmp(argv[1], "int") == 0) )
    {
        // internal -> External
        printf ("Get internal parameter for \"%s\"\n", argv[2]);
        retVal = aliasGetInternalName(argv[2], &releaseMem);
        if (retVal != NULL)
        {
            printf("Ext name:%s\n", argv[2]);
            printf("Int Name:%s\n\n", retVal);
            if (releaseMem)
                AnscFreeMemory (retVal);
        }
        else
        {
            printf("Error: mapping failed (Ext->Int): %s\n", argv[2]);
        }
    }
    else
    {
        //  internal -> External
        printf("Get external parameter for \"%s\"\n",argv[2]);
        retVal = aliasGetExternalName(argv[2], &releaseMem);
        if (retVal != NULL)
        {
            printf("Int name:%s\n", argv[2]);
            printf("Ext Name:%s\n\n", retVal);
            if (releaseMem)
                AnscFreeMemory (retVal);
        }
        else
        {
            printf("Error: mapping failed (Int->Ext): %s\n", argv[2]);
        }
    }
    return 0;
}
#endif
