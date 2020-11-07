#ifdef __linux__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

#include "fedora.h"
#include "heartbeat.h"
#include "unix.h"

void fedora_version()
{
    FILE *f_ptr;
    char buffer[50] = "";

    f_ptr = fopen(FED_VERSION, "r");

    if (f_ptr == NULL) {
        printf("Failed to open the file %s\n", FED_VERSION);
        if (f_ptr) {
            fclose(f_ptr);
        }
        exit(1);
    }

    fgets(buffer, sizeof(buffer), f_ptr);
    buffer[50] = '\0';
    fclose(f_ptr);

    printf("Version: %s", buffer);
}

void fedora_info(long minute, long hour, long day, double megabyte)
{
    long m = minute;
    long h = hour;
    long d = day;
    double meg = megabyte;

    struct sysinfo info;
    sysinfo(&info);

    struct utsname uinfo;
    uname(&uinfo);

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
