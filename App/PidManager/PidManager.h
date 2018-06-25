//
// Created by alex on 6/24/18.
//

#ifndef PACK_PIDMANAGER_H
#define PACK_PIDMANAGER_H

#endif //PACK_PIDMANAGER_H


struct upid {
    int nr;                     // the PID value
    struct pid_namespace *ns;   // namespace where this PID is relevant
    // ...
};

struct pid {
    // ...
    int level;                  // number of upids
    struct upid numbers[0];     // array of upids
};