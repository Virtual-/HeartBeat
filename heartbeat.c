#include <stdio.h>

#include "fedora.h"
#include "netbsd.h"
#include "heartbeat.h"

int main(int argc, char *argv[])
{
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;
    const double megabyte = 1024 * 1024;


    #ifdef __linux__
    print_fedora(minute, hour, day, megabyte);
    #endif

    #ifdef __NetBSD__
    print_netbsd();
    #endif

    return 0;
}
