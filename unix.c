#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Unix.c is mainly comprised of functions that can be used across multiple GNU/Linux distributions and even *BSD systems.


/* GNU/Linux + *BSD supported function.
 * Get's number of packages installed by calling a shell command then
 * saving the output into a file in /tmp/ and then counting by line.
 */
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

/* GNU/Linux Function.
 * Get's the current version of the GNU/Linux distro by reading a file
 * commonly stored in /etc/
 *
 * This will work on BSD but typically only GNU/Linux distributions do this.
 *
 * Example: /etc/fedora-release
 */
void linux_version(const char *filename)
{
    FILE *f_ptr;
    char buffer[50] = "";

    f_ptr = fopen(filename, "r");

    if (f_ptr == NULL) {
        printf("Failed to open the file %s\n", filename);
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
