# include "../inc/xsysc.hpp"


int main(void)
{
    XSYSC__ParseCmd("history -c");
    XSYSC__ParseCmd("   history -c");
    XSYSC__ParseCmd("   history -c   ");
    XSYSC__ParseCmd("history -c   ");
    return (0);
}