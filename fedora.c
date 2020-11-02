#define FED_VERSION "/etc/fedora-release"
#define FED_PACKAGEMAN "/usr/bin/dnf"
#define FED_TEMPPACKAGE "/tmp/fedorapackagelist"

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
