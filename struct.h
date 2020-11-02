//Daniel Kantor & Derek Levine
#ifndef STRUCT_H
#define STRUCT_H

struct data{ //Struct to store the data that the processors return after execution
    data(long sp, long r, int p, long se) : speed(sp), remainingServiceTime(r), processID(p), serviceTime(se){}
    long speed;
    long remainingServiceTime;
    long processID;
    long serviceTime;
};

struct node{ //Struct to store the randomly generated serive time and memory size. It also stores the process ID of the process. This struct will be interested into a queue
    node(long s, int m, int i) : serviceTime(s), memorySize(m), processID(i){}
    long serviceTime;
    int memorySize;
    int processID;
};

struct priorityNode{//Struct to store the randomly generated serive time and memory size. It also stores the process ID of the process. This data in this struct will be inserted into a min priority queue
    priorityNode(long s, int m, int i) : serviceTime(s), memorySize(m), processID(i){}
    long serviceTime;
    int memorySize;
    int processID;

    bool operator<(const priorityNode& compare) const{ //Operator used to compare values of serviceTime, to order the priority queue from smallest to largest
        return serviceTime > compare.serviceTime;
    }
};

#endif