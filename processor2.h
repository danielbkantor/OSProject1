//Daniel Kantor & Derek Levine
#ifndef PROCESSOR2_H
#define PROCESSOR2_H

#include <unistd.h>
#include <iostream>
#include "struct.h"
using namespace std;

//sets up the imports and returns of processor2 so it can be called from FIFO.cpp and SJF.cpp
data processor2(long speed2, long sTime, int processID, long serviceTime);

#endif