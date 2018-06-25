#ifndef PACK_PACKREADER_H
#define PACK_PACKREADER_H

#endif //PACK_PACKREADER_H


#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <syscall.h>
#include <unistd.h>

#include <string.h>

#define STACK_SIZE (1024 * 1024)
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

#define NAME "#NAME"
#define RUN "#RUN"
#define USR "#USR"
#define ENV "#ENV"
#define NET "#NET"
#define ISO "#ISO"
#define CGROUP "#CGROUP"

#define NAME_MODE 0
#define RUN_MODE 1
#define USR_MODE 2
#define ENV_MODE 3
#define NET_MODE 4
#define ISO_MODE 5
#define CGROUP_MODE 6

int switch_mode(char *MODE);

int run_mode_process(char *line);

int iso_mode_process(char *img_filepath, char *container_name);

int net_mode_process(char *ip_address_host_veth0, char *ip_address_guest_veth1);

int net_mode_process_host(char *ip_address_host_veth0);

int net_mode_process_guest(char *ip_address_guest_veth1);

int name_mode_process(char *name);

int usr_mode_process();

int env_mode_process();

int cgroup_mode_process();