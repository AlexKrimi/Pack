
#ifndef PACK_CONTAINER_H
#define PACK_CONTAINER_H

#endif //PACK_CONTAINER_H

#pragma once


struct Container {
    int network;
    int isolate;
    char host_ip[16];
    char guest_ip[16];
    char *name;
    char *user;
    char *location;
};

struct Container new_container();