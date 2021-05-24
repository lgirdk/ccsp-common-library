#ifndef  __CUSTOM_ALIAS_UTILS_H__
#define  __CUSTOM_ALIAS_UTILS_H__

#define MAX_ALIAS 5

typedef struct aliasNames_t
{
    char* aliasName[MAX_ALIAS];
    unsigned char aliasCount;
}aliasNames_t;

const char* aliasGetInternalName(char* externalName, int* releaseMem);
const char* aliasGetExternalName(char* internalName, int* releaseMem);

const char* lgiAliasGetInternalName(char* externalName);
const char* lgiAliasGetExternalName(char* internalName);
aliasNames_t* lgiAliasGetInternalNames(char* externalName);
const char* lgiAliasGetNextName(struct aliasNames_t* pAliasNames);
void lgiAliasFreeNamesList(struct aliasNames_t* pAliasNames);

#endif
