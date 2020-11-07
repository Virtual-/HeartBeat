#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void get_packages(const char *command)
{
    int count = 0;
    int currchar = 0;
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("There was an error with a child process.");
    } else if (child_pid == 0) { 
        execlp( "/bin/sh", "/bin/sh", "-c", command, (char *)NULL );
    } else {

       wait(NULL); // Wait for the child process to finish otherwise we may get a NULL pointer back from fopen();

        FILE *f_ptr;
    
        f_ptr = fopen("/tmp/pkglist", "r");

        if (f_ptr == NULL) {
            printf("Failed to open the file %s\n", "/tmp/pkglist");
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
        printf("Packages: %d\n", count);
    }
}
