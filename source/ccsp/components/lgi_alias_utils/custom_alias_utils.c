#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ansc_platform.h"

//=============================================================================

#include "custom_alias_utils.h"

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
        else
        {
            out[i++] = *in++;
        }
    }
    out[i] = '\0';
    return 0;
}

//=============================================================================

const char* aliasGetInternalName(char* externalName, int* releaseMem)
{
    const char* retVal = NULL;
    struct Alias_t* pStAlias;
    int indexIds[10];
    int indexIdCount;
    char temp_buf[BUF_SIZE];

    *releaseMem = 0;
    if (NULL == externalName) return NULL;

    convertInstaceIDForMapping(externalName, temp_buf, indexIds, &indexIdCount);

    pStAlias = map_ExternalToInternal(temp_buf, strlen(temp_buf));
    if (NULL != pStAlias)
    {
        if (indexIdCount == 0)
        {
            retVal = pStAlias->aliasName;
        }
        else
        {
            int len = 0;
            restoreInstaceIDAfterMapping(pStAlias->aliasName, temp_buf, indexIds, indexIdCount);
            len = strlen (temp_buf);
            retVal = AnscAllocateMemory(len + 1);
            if (retVal)
            {
                strcpy (retVal, temp_buf);
                *releaseMem = 1;
            }
        }
//            printf("%s: %s->%s\n", __FUNCTION__, externalName, retVal);
    }
    return retVal;
}

//=============================================================================

const char* aliasGetExternalName(char* intrnalName, int* releaseMem)
{
    const char* retVal = NULL;
    struct Alias_t* pStAlias;
    int indexIds[10];
    int indexIdCount;
    char temp_buf[BUF_SIZE];

    *releaseMem = 0;
    if (NULL == intrnalName) return NULL;

    convertInstaceIDForMapping(intrnalName, temp_buf, indexIds, &indexIdCount);

    pStAlias = map_InternalToExternal(temp_buf, strlen(temp_buf));
    if (NULL != pStAlias)
    {
        if (indexIdCount == 0)
        {
            retVal = pStAlias->aliasName;
        }
        else
        {
            int len = 0;
            restoreInstaceIDAfterMapping(pStAlias->aliasName, temp_buf, indexIds, indexIdCount);
            len = strlen (temp_buf);
            retVal = AnscAllocateMemory(len + 1);
            if (retVal)
            {
                strcpy (retVal, temp_buf);
                *releaseMem = 1;
            }
        }
//            printf("%s: %s->%s\n", __FUNCTION__, intrnalName, retVal);
    }
    return retVal;
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
