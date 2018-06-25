//
// Created by alex on 6/22/18.
//
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

#define NAME_MODE 0
#define RUN_MODE 1
#define USR_MODE 2
#define ENV_MODE 3
#define NET_MODE 4
#define ISO_MODE 5

int switch_mode(char* MODE);

char** fileReader(char* filepath);