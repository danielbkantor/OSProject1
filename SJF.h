//Daniel Kantor & Derek Levine
#ifndef SJF_H
#define SJF_H

#include <queue>
#include <iostream>
#include "struct.h"
using namespace std;

//Sets up the imports for SJF so it can be called from createProcess.cpp
void SJF(priority_queue<priorityNode> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4, int scenario);

#endif