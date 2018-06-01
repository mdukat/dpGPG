#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <syslog.h>

void init()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        exit(EXIT_FAILURE);
    } else if(pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    openlog("dpGPG-daemon", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    umask(0);

    pid_t sid = setsid();
    if(sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
