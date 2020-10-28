#ifndef FIFO_H
#define FIFO_H

#include <queue>
#include <iostream>
using namespace std;

struct node{ //Struct to store the two random values in a container
    node(long s, int m) : serviceTime(s), memorySize(m){}
    long serviceTime;
    int memorySize;
};

void FIFO(queue<node> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4);

#endif