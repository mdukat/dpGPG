#include <string>
#include <unistd.h>
#include <sys/wait.h>

void sync_drives()
{
    pid_t pID = fork();
    if(pID == 0)
    {
        execl("/bin/sync", "/bin/sync", (char*) 0);
    } else {
        waitpid(pID, NULL, 0);
    }
}

int format_and_mount(std::string drive)
{
    //format
    int state = 0;
    pid_t pID = fork();
    if(pID == 0)
    {
        execl("/sbin/mkfs.fat", "/sbin/mkfs.fat", drive.c_str(), (char*) 0);
    } else {
        waitpid(pID, &state, 0);
    }
    if(state != 0)
    {
        return 1;
    }

    //mount
    pID = fork();
    if(pID == 0)
    {
        execl("/bin/mkdir", "/bin/mkdir", "-p", "/tmp/dpGPG/pen-generator", (char*) 0);
    } else {
        waitpid(pID, &state, 0);
    }
    if(state != 0)
    {
        return 2;
    }

    pID = fork();
    if(pID == 0)
    {
        execl("/bin/mount", "/bin/mount", drive.c_str(), "/tmp/dpGPG/pen-generator", (char*) 0);
    } else {
        waitpid(pID, &state, 0);
    }
    if(state != 0)
    {
        return 3;
    }
    return 0;
}

void clear_folders()
{
    pid_t pID = fork();
    if(pID == 0)
    {
        execl("/bin/umount", "/bin/umount", "/tmp/dpGPG/pen-generator", (char*) 0);
    } else {
        waitpid(pID, NULL, 0);
    }

    pID = fork();
    if(pID == 0)
    {
        execl("/bin/rm", "/bin/rm", "-r", "/tmp/dpGPG/pen-generator", (char*) 0);
    } else {
        waitpid(pID, NULL, 0);
    }
}

int copy_secring(std::string secring_location)
{
    int status = 0;

    pid_t pID = fork();
    if(pID == 0)
    {
        execl("/bin/cp", "/bin/cp", secring_location.c_str(), "/tmp/dpGPG/pen-generator/.", (char*) 0);
    } else {
        waitpid(pID, &status, 0);
    }

    if(status != 0)
    {
        return 1;
    }
    return 0;
}
