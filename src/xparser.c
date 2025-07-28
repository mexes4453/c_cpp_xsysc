#include "../inc/xparser.h"

size_t XPARSER__StrLen(char const *s)
{
    size_t i;

    i = 0;
    if (s)
    {
        while (*(s + i) != XPARSER__CHAR_NULL)
        {
            i++;
        }
    }
    return (i);
}

char *XPARSER__StrChr(const char *str, int chr)
{
    unsigned char c;
    char *s;
    char *ret;

    s = (char *)str;
    c = (unsigned char)chr;
    ret = NULL;
    while ((*s) != XPARSER__CHAR_NULL)
    {
        if ((*s) == c)
        {
            ret = s;
            break;
        }
        s++;
    }
    /* User may search for null char '\0' */
    if ((c) == XPARSER__CHAR_NULL)
    {
        ret = s;
    }
    return (ret);
}

char **XPARSER__ParseCmd(char const *s)
{

    char **cmdArgs;
    size_t tokenCnt = 0;

    tokenCnt = XPARSER__GetTokenCount(s);
#ifdef __DEBUG_XPARSER__
    printf("%s: length(%ld); tokens(%ld)\n", s, XPARSER__StrLen(s), tokenCnt);
#endif

    /* Allocate memory for token strings */
    cmdArgs = (char **)malloc(sizeof(char *) * (tokenCnt + 1));

    /* Convert token to single string and assign to args list */
    XPARSER__AddArgsToList(s, tokenCnt, cmdArgs);

    /* Null terminate argv list */
    cmdArgs[tokenCnt] = NULL;

    /* Free resoures on heap */
    //XPARSER__DestroyArgsList(&cmdArgs);

    return (cmdArgs);
}

void *XPARSER__DestroyArgsList(char ***listAdr)
{
    char **argsList = NULL;
    size_t idx = 0;

    if (listAdr)
    {
        argsList = *listAdr;
        while (argsList[idx] != NULL)
        {
            if (argsList[idx])
            {
                free(argsList[idx]);
                argsList[idx] = NULL;
            }
            idx++;
        }
        free(argsList);
        *listAdr = NULL;
    }
    return (NULL);
}

size_t XPARSER__GetTokenCount(char const *str)
{
    size_t  tokenCnt = 0;
    char   *s;
    char   *pStart;
    char   *pEnd;

    s = (char *)str;
    while ( s && (*s) != XPARSER__CHAR_NULL)
    {
        pStart = NULL;
        pEnd = NULL;
        s = XPARSER__GetToken(s, &pStart, &pEnd);
        if (pStart)
        {
            tokenCnt++;
        }
        else { break ;}
    }
    return (tokenCnt);
}

char *XPARSER__GetToken(char const *str, char **pStart, char **pEnd)
{
    char *s;

    s = (char *)str;
    /* Find the start(first character) of a string */
    *pStart = XPARSER__FindNonWhiteSpace(s);
    if (*pStart)
    {
        /*>
         * skip the followin string characters till last chr in string just
         * before a whitespace char */
        s = XPARSER__FindWhiteSpace(*pStart);
        if (s)
        {
            *pEnd = s;
        }
        else /* string terminator character found */
        {
            *pEnd = (*pStart) + XPARSER__StrLen(*pStart);
        }
    }
    return (s);
}




char *XPARSER__FindNonWhiteSpace(char const *str)
{
    char *s = (char *)str;
    char *ret = NULL;
    
    while ( s && ((*s) != XPARSER__CHAR_NULL) )
    {
        if (!XPARSER__StrChr(XPARSER__WHITESPACE_CHARS, *s))
        {
            ret = s;
            break ;
        }
        s++;
    }
    return (ret);
}




char *XPARSER__FindWhiteSpace(char const *str)
{
    char *s = (char *)str;
    char *ret = NULL;
    
    while ( s && ((*s) != XPARSER__CHAR_NULL) )
    {
        if (XPARSER__StrChr(XPARSER__WHITESPACE_CHARS, *s))
        {
            ret = s;
            break ;
        }
        s++;
    }
    return (ret);
}




void  XPARSER__AddArgsToList(char const *str, size_t cnt, char **argsList)
{
    size_t  idx=0;
    size_t  tokenLen = 0;
    char   *arg = NULL;
    char   *pStart = NULL;
    char   *pEnd   = NULL;
    char   *s   = (char *)str;

    /* Convert token to single string and assign to args list */
    while (idx < cnt)
    {
        s = XPARSER__GetToken(s, &pStart, &pEnd);
        tokenLen = pEnd - pStart;
        arg = (char *)malloc(tokenLen + 1);
        if (arg)
        {
            XPARSER__MemCpy(arg, pStart, tokenLen);
            arg[tokenLen] = XPARSER__CHAR_NULL;
            argsList[idx] = arg;
#ifdef __DEBUG_XPARSER__
            printf("%ld: %s; len(%ld)\n", idx, pStart, pEnd - pStart);
            printf("%ld: %s; len(%ld)\n", idx, argsList[idx], XPARSER__StrLen(argsList[idx]));
#endif
        }
        idx++;
    }
}




void	*XPARSER__MemCpy(void *dest, const void *src, size_t n)
{	
	size_t			i;
	unsigned char	*dest2;
	unsigned char	*src2;

	i = 0;
	dest2 = (unsigned char *) dest;
	src2 = (unsigned char *) src;
	if (!dest || !src)
		return (NULL);
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}
