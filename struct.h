#ifndef STRUCT_H
#define STRUCT_H

struct data{ //Struct to store the two random values in a container
    data(long sp, long r, int p) : speed(sp), remainingServiceTime(r), processID(p){}
    long speed;
    long remainingServiceTime;
    long processID;
};

#endif