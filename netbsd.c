#ifdef __NetBSD__
#include <stdio.h>
#include <sys/utsname.h>

#include "heartbeat.h"
#include "unix.h"

// This is the NetBSD specific C source file.

void print_netbsd() 
{
    struct utsname uinfo;
    uname(&uinfo);

    printf("Version: %s %s\n", uinfo.sysname, uinfo.release);
    get_packages("pkg_info > /tmp/pkglist");
    printf("Shell: %s\n", printenv("SHELL"));
}

#endif
