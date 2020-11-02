#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>

#include <sys/sysinfo.h>
#include "fedora.h"
#include "heartbeat.h"

void fedoraVer()
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

void fedoraPackages()
{
    int count = 0;
    int currchar = 0;
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("There was an error with a child process.");
    } else if (child_pid == 0) { 
        execlp( "/bin/sh", "/bin/sh", "-c", "dnf list installed > /tmp/fedorapackagelist", (char *)NULL );
    } else {

       wait(NULL); // Wait for the child process to finish otherwise we may get a NULL pointer back from fopen();

        FILE *f_ptr;
    
        f_ptr = fopen(FED_TEMPPACKAGE, "r");

        if (f_ptr == NULL) {
            printf("Failed to open the file %s\n", FED_TEMPPACKAGE);
            if (f_ptr) {
                fclose(f_ptr);
            }
            exit(1);
        }

        while((currchar = fgetc(f_ptr)) != EOF) {
            if (currchar == '\n') {
                count = count + 1;
            }
        }

        fclose(f_ptr);
        count = count - 2; //Removing two newlines that aren't actually packages but excess output from DNF

        printf("Packages: %d\n", count);
    }
}

void fedoraInfo(long minute, long hour, long day, double megabyte)
{
    long m = minute;
    long h = hour;
    long d = day;
    double meg = megabyte;

    struct sysinfo info;
    sysinfo(&info);

    struct utsname uinfo;
    uname(&uinfo);

    printf("Shell: %s\n", printEnv("SHELL"));
    printf("Uptime: %ld day(s), %ld hour(s) and %ld minute(s)\n", (info.uptime / d), (info.uptime % d) / h, (info.uptime % h) / m);
    printf("Memory: %5.1fMB Total, %5.1fMB Free\n", info.totalram / meg, info.freeram / meg);
    printf("Architechture: %s\n", uinfo.machine);
    printf("Kernel: %s %s\tBuilddate: %s\n", uinfo.sysname, uinfo.release, uinfo.version);
    printf("Machine name: %s\n", uinfo.nodename);
    printf("User: %s\n", printEnv("USER"));
    printf("CPU: %ld core(s)\n", sysconf(_SC_NPROCESSORS_ONLN));
}

#endif
