#ifdef __linux__

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

#include "fedora.h"
#include "heartbeat.h"
#include "unix.h"

// This is the Fedora specific C source file.


void print_fedora(long minute, long hour, long day, double megabyte)
{
    long m = minute;
    long h = hour;
    long d = day;
    double meg = megabyte;

    struct sysinfo info;
    sysinfo(&info);

    struct utsname uinfo;
    uname(&uinfo);

    linux_version(FED_VERSION); // FED_VERSION is defined in fedora.h
    get_packages("dnf list installed > /tmp/pkglist");
    printf("Shell: %s\n", printenv("SHELL"));
    printf("Uptime: %ld day(s), %ld hour(s) and %ld minute(s)\n", (info.uptime / d), (info.uptime % d) / h, (info.uptime % h) / m);
    printf("Memory: %5.1fMB Total, %5.1fMB Free\n", info.totalram / meg, info.freeram / meg);
    printf("Architechture: %s\n", uinfo.machine);
    printf("Kernel: %s %s\tBuilddate: %s\n", uinfo.sysname, uinfo.release, uinfo.version);
    printf("Machine name: %s\n", uinfo.nodename);
    printf("User: %s\n", printenv("USER"));
    printf("CPU: %ld core(s)\n", sysconf(_SC_NPROCESSORS_ONLN));
}

#endif
