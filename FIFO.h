//Daniel Kantor & Derek Levine
#ifndef FIFO_H
#define FIFO_H

#include <queue>
#include <iostream>
#include "struct.h"
using namespace std;

//Sets up the imports for FIFO so it can be called from createProcess.cpp
void FIFO(queue<node> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4, int scenario);

#endif