//Daniel Kantor & Derek Levine
#ifndef PROCESSOR4_H
#define PROCESSOR4_H

#include <unistd.h>
#include <iostream>
#include "struct.h"
using namespace std;

//sets up the imports and returns of processor4 so it can be called from FIFO.cpp and SJF.cpp
data processor4(long speed4, long sTime, int processID, long serviceTime);

#endif