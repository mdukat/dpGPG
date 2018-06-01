#include <unistd.h>
#include <iostream>
#include "daemonskeleton.hpp"
#include <syslog.h>
#include <fstream>

int main()
{
    init();
    syslog(LOG_NOTICE, "")

    int i = 0;

    while(1)
    {
        i++; //debug
        syslog(LOG_NOTICE, "%d", i);
        sleep(10);
    }

    exit(EXIT_SUCCESS);
}
