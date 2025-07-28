#ifndef XPARSER_H
# define XPARSER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define XPARSER__WHITESPACE_CHARS        ("\n\t\v\f\r ")
# define XPARSER__CHAR_NULL               ('\0')

size_t   XPARSER__StrLen(char const *s);
char    *XPARSER__StrChr(char const *str, int chr);
void	*XPARSER__MemCpy(void *dest, const void *src, size_t n);
char   **XPARSER__ParseCmd(char const *strCmd);
size_t   XPARSER__GetTokenCount(char const *str);
char    *XPARSER__GetToken(char const *str, char **pStart, char **pEnd);
char    *XPARSER__FindNonWhiteSpace(char const *str);
char    *XPARSER__FindWhiteSpace(char const *str);
void     XPARSER__AddArgsToList(char const *str, size_t cnt, char **argsList);
void    *XPARSER__DestroyArgsList(char ***argsList);

#endif /* XPARSER_H */
