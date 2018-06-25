//
// Created by alex on 6/24/18.
//
#include "PackReader.h"

int switch_mode(char *MODE) {
    if (strncmp(MODE, RUN, strlen(RUN)) == 0) {
        return RUN_MODE;
    }
    else
    if (strncmp(MODE, NAME, strlen(NAME)) == 0) {
        return NAME_MODE;
    }
    else
    if (strncmp(MODE, USR, strlen(USR)) == 0) {
        return USR_MODE;
    }
    else
    if (strncmp(MODE, ENV, strlen(ENV)) == 0) {
        return ENV_MODE;
    }
    else
    if (strncmp(MODE, NET, strlen(NET)) == 0) {
        return NET_MODE;
    }
    else
    if (strncmp(MODE, ISO, strlen(ISO)) == 0) {
        return ISO_MODE;
    }

    return -1;
}