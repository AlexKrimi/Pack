#include "App/PackReader/PackReader.h"
#include "App/Container/Container.h"

static char child_stack[STACK_SIZE];


static int child_fn(void *arg) {
//    printf("Clone internal PID: %ld\n", (long) getpid());
    pid_t child_pid = fork();
    struct Container *container = (struct Container *) arg;


    if (child_pid) {

        int pack_read_mode = 1; // is saying hat mode is now.
        // see list of modes in Readme.md or App/PackReader/PackReader.h

        int mode_changed = 0; // boolean true/false.
        FILE *fp;

        char pack_filepath[10] = "Packfile";

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        fp = fopen(pack_filepath, "r");
        if (fp == NULL)
            exit(EXIT_FAILURE);


        while ((read = getline(&line, &len, fp)) != -1) {
            if (switch_mode(line) >= 0) {
                pack_read_mode = switch_mode(line);
                mode_changed = 1;
            }
//            printf("\n\n%s", container->name);
//            printf("\n\n%s", container->location);
//            printf("\n\n%s", container->host_ip);

            // if we have just change the mode,
            // we do not process the line with mode changing itself
            if (mode_changed) {
                if (pack_read_mode == CGROUP_MODE)
                    cgroup_mode_process(child_pid);
                mode_changed = 0;
                continue;
            } else
                switch (pack_read_mode) {
                    case ISO_MODE: {
                        iso_mode_process(container->location, container->name);
                        break;
                    }
                    case NET_MODE: {
                        net_mode_process_guest(container->guest_ip);
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
                    case CGROUP_MODE: {
                        break;
                    }
                }

        }
        fclose(fp);

        // attach to container when it is ready
        char argv[100];
        char env[100];
        execve("/bin/bash", argv, env);


    } else {
        // we have to unmount namespace on container exit.
        waitpid(child_pid, NULL, 0);
//        system("sudo -S umount /proc");
        system("umount /proc");
    }
    _exit(EXIT_SUCCESS);
}


int main(void) {
    struct Container container = new_container();
//    container = read_as_host("Packfile", container);

    void *arg = (void *) &container;
    pid_t child_pid = clone(child_fn, child_stack + STACK_SIZE, CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWNET | SIGCHLD,
                            arg);
    net_mode_process_host(child_pid, container.host_ip);

    waitpid(child_pid, NULL, 0);
    system("sudo -S umount /proc");
    _exit(EXIT_SUCCESS);
}