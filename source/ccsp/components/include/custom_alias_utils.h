#ifndef  __CUSTOM_ALIAS_UTILS_H__
#define  __CUSTOM_ALIAS_UTILS_H__

typedef struct Alias_t
{
    char *name;
    char *aliasName;
    unsigned char aliasStrict;
    unsigned char inputParamType;
}Alias_t;

const char* aliasGetInternalName(char* externalName, int* releaseMem);
const char* aliasGetExternalName(char* internalName, int* releaseMem);

#endif
