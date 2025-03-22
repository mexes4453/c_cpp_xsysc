#ifndef XSYSC_HPP
# define XSYSC_HPP
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>

# define XSYSC__PID_CHILD               (0)
# define XSYSC__WHITESPACE_CHARS        ("\n\t\v\f\r ")
# define XSYSC__CHAR_NULL               ('\0')
# define XSYSC__EXEC_ERROR_CHILD        (-5)

void     XSYSC__ExecuteCmd(char const *cmd);
size_t   XSYSC__StrLen(char const *s);
char    *XSYSC__StrChr(char const *str, int chr);
void	*XSYSC__MemCpy(void *dest, const void *src, size_t n);
char   **XSYSC__ParseCmd(char const *strCmd);
size_t   XSYSC__GetTokenCount(char const *str);
char    *XSYSC__GetToken(char const *str, char **pStart, char **pEnd);
char    *XSYSC__FindNonWhiteSpace(char const *str);
char    *XSYSC__FindWhiteSpace(char const *str);
void     XSYSC__AddArgsToList(char const *str, size_t cnt, char **argsList);
void    *XSYSC__DestroyArgsList(char ***argsList);

#endif /* XSYSC_HPP */