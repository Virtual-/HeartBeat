#include <stdio.h>
#include <stdlib.h>

#include "fedora.h"
#include "heartbeat.h"

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
    long minute = 60;
    long hour = minute * 60;
    long day = hour * 24;
    double megabyte = 1024 * 1024;


    #ifdef __linux__
    fedoraVer();
    fedoraPackages();
    fedoraInfo(minute, hour, day, megabyte);
    #endif

    return 0;
}
