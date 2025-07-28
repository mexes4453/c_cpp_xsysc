#include "../inc/xsysc.h"


void XSYSC__ExecuteCmd(char const *cmd)
{
    pid_t pidProc;
    char  **argsList = NULL;

    pidProc = fork();
    /* execute shell command in child process */
    if (pidProc == XSYSC__PID_CHILD)
    {
        argsList = XPARSER__ParseCmd(cmd);
        if (argsList)
        {
            printf("Executing child process\n");
            /* call exec here */
            execv(argsList[0], argsList);
            /*>
             *------------------------------
             * Child executes the following if unsuccessful */
            printf("Execution failed in child proc.\n");
            XPARSER__DestroyArgsList(&argsList);
            kill(pidProc,  SIGINT);
        }
    }
    /* Parent wait for child process */
    if (pidProc != XSYSC__PID_CHILD) wait(NULL);

    /* Manage resources */
    XPARSER__DestroyArgsList(&argsList);
}





