
#ifndef PACK_CONTAINER_H
#define PACK_CONTAINER_H

#endif //PACK_CONTAINER_H


struct Container{
    int network;
    int isolate;
    char* name;
    char* user;
};


struct Container* new_container(char* name, char* user, int network, int isolate);
struct Container* new_container_(int network, int isolate);