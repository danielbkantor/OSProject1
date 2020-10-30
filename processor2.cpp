#include "processor2.h"
#include "struct.h"

data processor2(long speed2, long sTime, int processID){    
    if(sTime > speed2 * 1000000000){
        sTime = sTime - (speed2 * 1000000000);
        cout << sTime << ":Processor 2";
        cout << " Process ID: " << processID << "\n";
        return data(speed2, sTime, processID);
    }
    else{
        cout << 0 << ":Processor 2 ";
        cout << " Process ID: " << processID << "\n";
        return data(speed2, 0, processID);
    }
}