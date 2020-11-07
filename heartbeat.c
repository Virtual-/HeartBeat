#include <stdio.h>
#include <stdlib.h>

#include "fedora.h"
#include "netbsd.h"
#include "heartbeat.h"

const char *printenv(const char *env)
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
    fedora_version();
    fedora_packages();
    fedora_info(minute, hour, day, megabyte);
    #endif

    #ifdef __NetBSD__
    print_netbsd();
    #endif

    return 0;
}
