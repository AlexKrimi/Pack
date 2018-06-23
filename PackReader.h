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


#define STACK_SIZE (1024 * 1024)
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

#define NAME "#NAME"
#define RUN "#RUN"
#define USR "#USR"
#define ENV "#ENV"
#define NET "#NET"
#define ISO "#ISO"

char** fileReader(char* filepath);