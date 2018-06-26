#include "Container.h"

//struct Container* new_container(char* name, char* user, int network, int isolate){
//    struct Container* container = malloc(sizeof(struct Container));
//    container.name = name;
//    container.user = user;
//    container.network = network;
//    container.isolate = isolate;
//    return container;
//}
//
//struct Container* new_container_(int network, int isolate){
//    struct Container* container = malloc(sizeof(struct Container));
//    container.name = "container";
//    container.user = "user";
//    container.network = network;
//    container.isolate = isolate;
//    return container;
//}

struct Container new_container(){
    struct Container container;
    container.isolate = 0;
    container.network = 0;
    container.name = "container_";
    strcpy (container.host_ip, "10.1.1.1");
    strcpy (container.guest_ip, "10.1.1.2");
    container.location = "../../";
    return container;
}