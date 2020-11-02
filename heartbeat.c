#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

#include "fedora.c"

const char *printEnv(const char *env)
{
    const char *arg = getenv(env);
    if (arg == NULL) {
        printf("Failed to get variable %s.\n", env);
    }

    return arg;
}

int main(int argc, char *argv[])
{
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;
    const double megabyte = 1024 * 1024;

    #ifdef __linux__
    struct sysinfo info;
    sysinfo(&info);

    struct utsname uinfo;
    uname(&uinfo);

    fedoraVer();
    fedoraPackages();
    printf("Shell: %s\n", printEnv("SHELL"));
    printf("Uptime: %ld day(s), %ld hour(s) and %ld minute(s)\n", (info.uptime / day), (info.uptime % day) / hour, (info.uptime % hour) / minute);
    printf("Memory: %5.1fMB Total, %5.1fMB Free\n", info.totalram / megabyte, info.freeram / megabyte);
    printf("Architechture: %s\n", uinfo.machine);
    printf("Kernel: %s %s\tBuilddate: %s\n", uinfo.sysname, uinfo.release, uinfo.version);
    printf("Machine name: %s\n", uinfo.nodename);
    printf("User: %s\n", printEnv("USER"));
    printf("CPU: %ld core(s)\n", sysconf(_SC_NPROCESSORS_ONLN));
    #endif

    return 0;
}
