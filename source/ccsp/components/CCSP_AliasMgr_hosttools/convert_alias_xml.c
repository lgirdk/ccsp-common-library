
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=============================================================================

#define custom_MAP_GPERF "custom_map_alias.gperf"
#define PARAM_TYPE_EXTERNAL 0
#define PARAM_TYPE_INTERNAL 1
#define BUF_SIZE 256

//=============================================================================

typedef struct Alias_t
{
    char aliasExtName[256];
    char aliasIntName[256];
    int aliasStrict;
}Alias_t;

static Alias_t g_AliasList[10000];

static int alias_ptr = 0;

//=============================================================================

static int WriteResultToFile()
{
    static const char* h_declaration =
        "%{\n" \
        "#include <stdio.h>\n" \
        "#include <string.h>\n\n" \
        "typedef struct Alias_t\n" \
        "{\n" \
        "    char *name;\n" \
        "    char *aliasName;\n" \
        "    unsigned char aliasStrict;\n" \
        "    unsigned char inputParamType;\n" \
        "}Alias_t; \n" \
        "%}\n";

    char temp_buf[1024];
    int i;

    // Create gperf file
    FILE* fp = fopen(custom_MAP_GPERF, "wt");
    if (fp == NULL)
    {
        printf("%s: Error: Unable to open file %s\n", __FUNCTION__, custom_MAP_GPERF);
        return -1;
    }
    // gperf section: declarations
    fputs(h_declaration, fp);
    fputs("struct Alias_t;\n", fp);

    // gperf section: keywords
    fputs("%%\n", fp);
    for (i = 0; i < alias_ptr; i++)
    {
        // External -> Internal Mapping
        snprintf(temp_buf, sizeof(temp_buf), "\"%s\",\"%s\",%d,%d\n", g_AliasList[i].aliasExtName, g_AliasList[i].aliasIntName, g_AliasList[i].aliasStrict, PARAM_TYPE_EXTERNAL);
        fputs(temp_buf, fp);
        // Internal -> External Mapping
        snprintf(temp_buf, sizeof(temp_buf), "\"%s\",\"%s\",%d,%d\n", g_AliasList[i].aliasIntName, g_AliasList[i].aliasExtName, g_AliasList[i].aliasStrict, PARAM_TYPE_INTERNAL);
        fputs(temp_buf, fp);
    }
    fputs("%%\n", fp);

    // gperf section: functions (currently it is in seperate file)

    fclose(fp);
    return 0;
}

//=============================================================================

static int updateAliasMap(int aliasStrict, char* paramStr1, char* paramStr2)
{
    char inStr[BUF_SIZE];
    char outStr[BUF_SIZE];
    int processDone = 0;

    char* pInP1 = NULL;
    char* pInP2 = NULL;
    char* pOutP1 = NULL;
    char* pOutP2 = NULL;
    int i;

    pInP1 = paramStr1;
    pOutP1 = paramStr2;

    if ( (NULL == pInP1) || (NULL == pOutP1) )
    {
        printf("Error: Alias mapping string...");
        return -1;
    }

    // start from 2rd node
    pInP2 = strstr(pInP1, ".");
    pOutP2 = strstr(pOutP1, ".");
    if ( (NULL == pInP2) || (NULL == pOutP2) )
    {
        printf("Error: Alias mapping string...");
        return -1;
    }
    pInP2++;
    pOutP2++;

    while (1)
    {
        size_t  len;
        int skip_update;

        skip_update = 0;
        if ((NULL == pInP2) || (NULL == pOutP2))
        {
            break;
        }

        inStr[0] = '\0';
        len = pInP2 - pInP1;
        pInP2 = strstr(pInP2, ".");
        if (NULL == pInP2)
        {
            if (strlen (paramStr1) > len)
            {
                strcpy (inStr, paramStr1);
                processDone = 1;
            }
            else
            {
                break;
            }
        }
        else
        {
            pInP2++;
            memcpy(inStr, pInP1, pInP2 - pInP1);
            inStr[pInP2 - pInP1] = '\0';
        }
        outStr[0] = '\0';
        len = pOutP2 - pOutP1;
        pOutP2 = strstr(pOutP2, ".");
        if (NULL == pOutP2)
        {
            if (strlen (paramStr2) > len)
            {
                strcpy (outStr, paramStr2);
            }
            else
            {
                break;
            }
        }
        else
        {
            pOutP2++;
            memcpy(outStr, pOutP1, pOutP2 - pOutP1);
            outStr[pOutP2 - pOutP1] = '\0';
        }
        if ((!aliasStrict) && (strcmp(inStr, outStr) == 0) )
            continue;
        for (i = 0; i < alias_ptr; i++)
        {
            if (!strcmp(g_AliasList[i].aliasExtName, inStr))
            {
                if (aliasStrict)
                {
                    g_AliasList[i].aliasStrict = aliasStrict;
                }
                skip_update = 1;
                break;
            }
        }
        if (skip_update)
            continue;
        if ((NULL != inStr) && (NULL != outStr))
        {
            strcpy (g_AliasList[alias_ptr].aliasExtName, inStr);
            strcpy(g_AliasList[alias_ptr].aliasIntName, outStr);
            g_AliasList[alias_ptr].aliasStrict = aliasStrict;
            alias_ptr++;
        }
        if (processDone == 1) break;
    }
    return 0;
}

//=============================================================================

static void remove_spaces(char* str)
{
    int count = 0;
    int i;

    for (i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}

//=============================================================================

int main(int argc, char* argv[])
{
    int state = 0;
    int aliasStrictFlag = 0;
    char aliasExtStr[BUF_SIZE];
    char aliasIntStr[BUF_SIZE];
    char temp_buf[BUF_SIZE];

    if (argc != 2)
    {
        printf("Error: Invalid argument...\n");
        return -1;
    }

    // open custom mapper xml file for alias mapping
    FILE* fp = fopen(argv[1], "rt");
    if (fp == NULL)
    {
        printf("Error: Unable to open input custom mapper file (%s)...", argv[1]);
        return -1;
    }

    while (0 == feof(fp))
    {
        if (fgets(temp_buf, sizeof(temp_buf), fp) == NULL)
            break;
        remove_spaces(temp_buf);
        if (temp_buf[strlen(temp_buf) - 1] == '\n')
        {
            temp_buf[strlen(temp_buf) - 1] = '\0';
        }
        switch (state)
        {
            case 0:
            {
                if (strcmp(temp_buf, "<ParamList>") == 0)
                {
                    state = 1;
                }
                break;
            }
            case 1:
            {
                if (strcmp(temp_buf, "<AliasList>") == 0)
                {
                    aliasExtStr[0] = '\0';
                    aliasIntStr[0] = '\0';
                    aliasStrictFlag = 0;
                    state = 2;
                }
            }
            break;
            case 2:
            {
                char* p1, * p2;
                p1 = strstr(temp_buf, "<Aliasstrict=");

                if (p1 != NULL)
                {
                    if (0 == strcmp(temp_buf, "<Aliasstrict=\"true\">"))
                    {
                        aliasStrictFlag = 1;
                    }
                    break;
                }
                p1 = strstr(temp_buf, "<External>");
                if (p1 != NULL)
                {
                    p1 += strlen("<External>");
                    p2 = strstr(p1, "</External>");
                    if ((p1 != NULL) && (p2 != NULL))
                    {
                        memcpy (aliasExtStr, p1, p2 - p1);
                        aliasExtStr[p2 - p1] = '\0';
                    }
                    else
                    {
                        //invalid xml tag.
                        printf("Error: Invalid xml tag (External)...\n");
                    }
                    break;
                }
                p1 = strstr(temp_buf, "<Internal>");
                if (p1 != NULL)
                {
                    p1 += strlen("<Internal>");
                    p2 = strstr(p1, "</Internal>");
                    if ((p1 != NULL) && (p2 != NULL))
                    {
                        memcpy(aliasIntStr, p1, p2 - p1);
                        aliasIntStr[p2 - p1] = '\0';
                    }
                    else
                    {
                        //invalid xml tag.
                        printf("Error: Invalid xml tag (Internal)... \n");
                    }
                }
                if ((aliasExtStr[0] != '\0') && (aliasIntStr[0] != '\0'))
                {
                    if (0 != updateAliasMap(aliasStrictFlag, aliasExtStr, aliasIntStr))
                    {
                        printf("Error: updating to map list...");
                    }
                    aliasExtStr[0] = '\0';
                    aliasIntStr[0] = '\0';
                    aliasStrictFlag = 0;
                }
            }
            break;
            default:
                break;
        }
    }
    printf("Alias map count = %d\n", alias_ptr);
    if (0 != WriteResultToFile())
    {
        printf ("Error: Creating gperf file...\n");
    }
    return 0;
}

//=============================================================================

