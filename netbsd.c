#ifdef __NetBSD__
#include <stdio.h>
#include <sys/utsname.h>

#include "heartbeat.h"

void testNetBSD() 
{
    struct utsname uinfo;
    uname(&uinfo);

    printf("Version: %s %s\n", uinfo.sysname, uinfo.release);
    printf("Packages:\n");
    printf("Shell: %s\n", printEnv("SHELL"));
}

#endif
