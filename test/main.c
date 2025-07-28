# include "../inc/xsysc.h"


int main(void)
{
    XPARSER__ParseCmd("history -c");
    XPARSER__ParseCmd("   history -c");
    XPARSER__ParseCmd("   history -c   ");
    XPARSER__ParseCmd("history -c   ");
    return (0);
}
