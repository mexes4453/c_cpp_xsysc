#include "../inc/xsysc.hpp"



void XSYSC__ExecuteCmd(char const *cmd)
{
    pid_t pidProc;
    char  **argsList = NULL;

    pidProc = fork();
    /* execute shell command in child process */
    if (pidProc == XSYSC__PID_CHILD)
    {
        argsList = XSYSC__ParseCmd(cmd);
        if (argsList)
        {
            printf("Executing child process\n");
            /* call exec here */
            execv(argsList[0], argsList);
            /*>
             *------------------------------
             * Child executes the following if unsuccessful */
            printf("Execution failed in child proc.\n");
            XSYSC__DestroyArgsList(&argsList);
            kill(pidProc,  SIGINT);
        }
    }
    /* Parent wait for child process */
    if (pidProc != XSYSC__PID_CHILD) wait(NULL);

    /* Manage resources */
    XSYSC__DestroyArgsList(&argsList);
}

size_t XSYSC__StrLen(char const *s)
{
    size_t i;

    i = 0;
    if (s)
    {
        while (*(s + i) != XSYSC__CHAR_NULL)
        {
            i++;
        }
    }
    return (i);
}

char *XSYSC__StrChr(const char *str, int chr)
{
    unsigned char c;
    char *s;
    char *ret;

    s = (char *)str;
    c = (unsigned char)chr;
    ret = NULL;
    while ((*s) != XSYSC__CHAR_NULL)
    {
        if ((*s) == c)
        {
            ret = s;
            break;
        }
        s++;
    }
    /* User may search for null char '\0' */
    if ((c) == XSYSC__CHAR_NULL)
    {
        ret = s;
    }
    return (ret);
}

char **XSYSC__ParseCmd(char const *s)
{

    char **cmdArgs;
    size_t tokenCnt = 0;

    tokenCnt = XSYSC__GetTokenCount(s);
#ifdef __DEBUG_XSYSC__
    printf("%s: length(%ld); tokens(%ld)\n", s, XSYSC__StrLen(s), tokenCnt);
#endif

    /* Allocate memory for token strings */
    cmdArgs = (char **)malloc(sizeof(char *) * (tokenCnt + 1));

    /* Convert token to single string and assign to args list */
    XSYSC__AddArgsToList(s, tokenCnt, cmdArgs);

    /* Null terminate argv list */
    cmdArgs[tokenCnt] = NULL;

    /* Free resoures on heap */
    //XSYSC__DestroyArgsList(&cmdArgs);

    return (cmdArgs);
}

void *XSYSC__DestroyArgsList(char ***listAdr)
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

size_t XSYSC__GetTokenCount(char const *str)
{
    size_t  tokenCnt = 0;
    char   *s;
    char   *pStart;
    char   *pEnd;

    s = (char *)str;
    while ( s && (*s) != XSYSC__CHAR_NULL)
    {
        pStart = NULL;
        pEnd = NULL;
        s = XSYSC__GetToken(s, &pStart, &pEnd);
        if (pStart)
        {
            tokenCnt++;
        }
        else { break ;}
    }
    return (tokenCnt);
}

char *XSYSC__GetToken(char const *str, char **pStart, char **pEnd)
{
    char *s;

    s = (char *)str;
    /* Find the start(first character) of a string */
    *pStart = XSYSC__FindNonWhiteSpace(s);
    if (*pStart)
    {
        /*>
         * skip the followin string characters till last chr in string just
         * before a whitespace char */
        s = XSYSC__FindWhiteSpace(*pStart);
        if (s)
        {
            *pEnd = s;
        }
        else /* string terminator character found */
        {
            *pEnd = (*pStart) + XSYSC__StrLen(*pStart);
        }
    }
    return (s);
}




char *XSYSC__FindNonWhiteSpace(char const *str)
{
    char *s = (char *)str;
    char *ret = NULL;
    
    while ( s && ((*s) != XSYSC__CHAR_NULL) )
    {
        if (!XSYSC__StrChr(XSYSC__WHITESPACE_CHARS, *s))
        {
            ret = s;
            break ;
        }
        s++;
    }
    return (ret);
}




char *XSYSC__FindWhiteSpace(char const *str)
{
    char *s = (char *)str;
    char *ret = NULL;
    
    while ( s && ((*s) != XSYSC__CHAR_NULL) )
    {
        if (XSYSC__StrChr(XSYSC__WHITESPACE_CHARS, *s))
        {
            ret = s;
            break ;
        }
        s++;
    }
    return (ret);
}




void  XSYSC__AddArgsToList(char const *str, size_t cnt, char **argsList)
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
        s = XSYSC__GetToken(s, &pStart, &pEnd);
        tokenLen = pEnd - pStart;
        arg = (char *)malloc(tokenLen + 1);
        if (arg)
        {
            XSYSC__MemCpy(arg, pStart, tokenLen);
            arg[tokenLen] = XSYSC__CHAR_NULL;
            argsList[idx] = arg;
#ifdef __DEBUG_XSYSC__
            printf("%ld: %s; len(%ld)\n", idx, pStart, pEnd - pStart);
            printf("%ld: %s; len(%ld)\n", idx, argsList[idx], XSYSC__StrLen(argsList[idx]));
#endif
        }
        idx++;
    }
}




void	*XSYSC__MemCpy(void *dest, const void *src, size_t n)
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
