#ifndef XSYSC_H
# define XSYSC_H
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../inc/xparser.h"

# define XSYSC__PID_CHILD               (0)
# define XSYSC__EXEC_ERROR_CHILD        (-5)

void     XSYSC__ExecuteCmd(char const *cmd);

#endif /* XSYSC_H */
