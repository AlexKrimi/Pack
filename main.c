#include "App/PackReader/PackReader.h"
#include "App/Container/Container.h"

static char child_stack[STACK_SIZE];

static int child_fn(void) {
//    printf("Clone internal PID: %ld\n", (long) getpid());
    pid_t child_pid = fork();



    if (child_pid) {

        int pack_read_mode = 1;
        int mode_changed = 0;

        FILE *fp;

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        fp = fopen("Packfile", "r");
        if (fp == NULL)
            exit(EXIT_FAILURE);


        while ((read = getline(&line, &len, fp)) != -1) {
            if (switch_mode(line) >= 0) {
                pack_read_mode = switch_mode(line);
                mode_changed = 1;
            }
            if (mode_changed) {
                mode_changed = 0;
            } else
                switch (pack_read_mode) {
                    case ISO_MODE: {

                        iso_mode_process("/home/alex/Workspace/Pack", "xz");
                        break;
                    }
                    case NET_MODE: {
                        net_mode_process_guest("10.1.1.2");
                        break;
                    }

                    case RUN_MODE: {
                        run_mode_process(line);
                        break;
                    }

                    case NAME_MODE: {

                        break;
                    }

                    case USR_MODE: {

                        break;
                    }

                    case ENV_MODE: {

                        break;
                    }
                }

        }
        fclose(fp);


        char argv[100];
        char env[100];
        execve("/bin/bash", argv, env);
    } else {
        waitpid(child_pid, NULL, 0);
        system("umount /proc");
    }
    _exit(EXIT_SUCCESS);
}


int main(void) {
    pid_t child_pid = clone(child_fn, child_stack + STACK_SIZE, CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWNET | SIGCHLD,
                            NULL);

    char str[256];
    strcpy(str, "ip link add name veth0 type veth peer name veth1 netns ");
    char buffer[16];
    snprintf(buffer, 10, "%d", child_pid);
    strcat(str, buffer);
    system(str);

    system("ifconfig veth0 10.1.1.1/24 up");

    waitpid(child_pid, NULL, 0);
//    system("umount /proc");
    _exit(EXIT_SUCCESS);
}