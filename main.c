#include "App/PackReader/PackReader.h"
#include "Container.h"

static char child_stack[STACK_SIZE];

static int child_fn(void) {
//    printf("Clone internal PID: %ld\n", (long) getpid());
    pid_t child_pid = fork();
    system("mount -t proc proc /proc --make-private");

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


        Container container = malloc(sizeof(Container));

        while ((read = getline(&line, &len, fp)) != -1) {
            if (switch_mode(line) >= 0)
                pack_read_mode = switch_mode(line);
            switch (pack_read_mode) {
                case ISO_MODE: {
                    container.isolate = 1;
                    system("dd if=/dev/zero of=/home/alex/Workspace/Pack/container_main.img bs=1M count=1024");

                    system("losetup /dev/loop7 container_main.img");
                    system("mkfs.ext4 /home/alex/Workspace/Pack/container_main.img 100");

                    system("touch /home/alex/Workspace/Pack/container_main.img");
s
                    system("mount -t ext4 /dev/loop7 /home/alex/Workspace/Pack/container_main.img");
                    break;
                }
                case NET_MODE: {
                    system("ip link");
                    system("ifconfig veth1 10.1.1.2/24 up");
                    break;
                }

                case RUN_MODE: {
                    system(line);
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

//        char argv[100];
//        char env[100];
//        execve("/bin/bash", argv, env);
    } else {
        waitpid(child_pid, NULL, 0);
        system("umount /proc");
        printf("PARENT PROCESS");
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
    _exit(EXIT_SUCCESS);
}