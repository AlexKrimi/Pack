#include "PackReader.h"


int switch_mode(char *MODE) {
    if (strncmp(MODE, RUN, strlen(RUN)) == 0) {
        return RUN_MODE;
    } else if (strncmp(MODE, NAME, strlen(NAME)) == 0) {
        return NAME_MODE;
    } else if (strncmp(MODE, USR, strlen(USR)) == 0) {
        return USR_MODE;
    } else if (strncmp(MODE, ENV, strlen(ENV)) == 0) {
        return ENV_MODE;
    } else if (strncmp(MODE, NET, strlen(NET)) == 0) {
        return NET_MODE;
    } else if (strncmp(MODE, ISO, strlen(ISO)) == 0) {
        return ISO_MODE;
    }

    return -1;
}

int run_mode_process(char *line) {
    if (strcmp(line, "")) {
        system(line);
        return 1;
    }
    return 0;
}


int iso_mode_process(char *img_filepath, char *container_name) {
    int is_something_bad_happened = 0;
    if (!strcmp(img_filepath, "")) {
        img_filepath = "~";
        is_something_bad_happened = 1;
    }
    if (!strcmp(img_filepath, "")) {
        container_name = "container";
        is_something_bad_happened = 1;
    }
    char image_full_path[256];
    sprintf(image_full_path, "%s/%s.img", img_filepath, container_name);

    system("mount -t proc proc /proc --make-private");


    char command_with_image_path[256] = "";

    sprintf(command_with_image_path, "dd if=/dev/zero of=%s bs=1M count=1024", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';

    sprintf(command_with_image_path, "losetup /dev/loop7 %s", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';

    sprintf(command_with_image_path, "mkfs.ext4 %s 100", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';

    sprintf(command_with_image_path, "touch %s", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';

    sprintf(command_with_image_path, "mount -t ext4 /dev/loop7 %s", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';

    return is_something_bad_happened;
}

int net_mode_process_guest(char *ip_address_guest_veth1) {
    int is_something_bad_happened = 0;
    if (!strcmp(ip_address_guest_veth1, "")) {
        ip_address_guest_veth1 = "10.1.1.1";
        is_something_bad_happened = 1;
    }
    system("ip link");

    char command_with_ip_address[256];

    sprintf(command_with_ip_address, "ifconfig veth1 %s/24 up", ip_address_guest_veth1);
    system(command_with_ip_address);
    return is_something_bad_happened;
}


int net_mode_process_host(pid_t child_pid, char *ip_address_host_veth0) {
    int is_something_bad_happened = 0;
    if (!strcmp(ip_address_host_veth0, "")) {
        ip_address_host_veth0 = "10.1.1.1";
        is_something_bad_happened = 1;
    }
    char str[256];
    strcpy(str, "ip link add name veth0 type veth peer name veth1 netns ");
    char buffer[16];
    snprintf(buffer, 10, "%d", child_pid);
    strcat(str, buffer);
    system(str);

    char command_with_ip_address[256];

    sprintf(command_with_ip_address, "ifconfig veth0 %s/24 up", ip_address_host_veth0);
    system(command_with_ip_address);
    return is_something_bad_happened;
}

int cgroup_mode_process(pid_t child_pid){
    system("mkdir /sys/fs/cgroup/cpu/demo");
    system("echo 50000 > /sys/fs/cgroup/cpu/demo/cpu.cfs_quota_us");
    system("echo 100000 > /sys/fs/cgroup/cpu/demo/cpu.cfs_period_us");
    char command_with_image_path[256] = "";
    sprintf(command_with_image_path, "echo %d > /sys/fs/cgroup/cpu/demo/tasks", child_pid);
    system(command_with_image_path);
    return 0;
}


struct Container read_as_host(char *pack_filepath, struct Container container) {
    printf(11111111111111111111111111111111);
    int pack_read_mode = 1; // is saying hat mode is now.
    // see list of modes in Readme.md or App/PackReader/PackReader.h

    int mode_changed = 0; // boolean true/false.
    int lines_read = 0;



    FILE *fp;

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
        // if we have just change the mode,
        // we do not process the line with mode changing itself
        if (mode_changed) {
            mode_changed = 0;
            continue;
        } else
            switch (pack_read_mode) {
                case ISO_MODE: {
                    if (strcmp(line, "")) {
                        container.location = line;
                    }
                    break;
                }
                case NET_MODE: {
                    if (strcmp(line, "")) {
                        if (lines_read == 0){
                            strcpy(container.host_ip, line);
                            ++lines_read;
                        }
                        else
                            strcpy(container.guest_ip, line);
                    }
                    break;
                }

                case RUN_MODE: {
                    break;
                }

                case NAME_MODE: {

                    if (strcmp(line, "")) {
                        container.name = line;
                    }
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
    printf("\n\n\n\n\n\n\nNAME: %s\n\n\n\n\n\n\n", container.name);
    printf("\n\n\n\n\n\n\nLocation: %s\n\n\n\n\n\n\n", container.location);
    return container;
}