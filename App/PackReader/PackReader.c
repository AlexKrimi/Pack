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

    printf("\n\n\nIM HERE!!!!!!!!!!!!!!!!!!!!!!!   %s\n\n\n", image_full_path);

    char command_with_image_path[256] = "";

    sprintf(command_with_image_path, "dd if=/dev/zero of=%s bs=1M count=1024", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';
    printf(command_with_image_path);

    sprintf(command_with_image_path, "losetup /dev/loop7 %s", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';
    printf(command_with_image_path);

    sprintf(command_with_image_path, "mkfs.ext4 %s 100", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';
    printf(command_with_image_path);

    sprintf(command_with_image_path, "touch %s", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';
    printf(command_with_image_path);

    sprintf(command_with_image_path, "mount -t ext4 /dev/loop7 %s", image_full_path);
    system(command_with_image_path);
    command_with_image_path[0] = '\0';
    printf(command_with_image_path);

    free(command_with_image_path);

    return is_something_bad_happened;
}

int net_mode_process_guest(char *ip_address_guest_veth1) {
    system("ip link");

    char command_with_ip_address[256];

    sprintf(command_with_ip_address, "ifconfig veth1 %s/24 up", ip_address_guest_veth1);
    system(command_with_ip_address);
    free(command_with_ip_address);
}


int net_mode_process_host(char *ip_address_host_veth0) {
    system("ip link");

    char command_with_ip_address[256];

    sprintf(command_with_ip_address, "ifconfig veth1 %s/24 up", ip_address_guest_veth1);
    system(command_with_ip_address);
    free(command_with_ip_address);
}