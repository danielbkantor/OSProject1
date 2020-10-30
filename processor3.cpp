#include "processor3.h"
#include "struct.h"

data processor3(long speed3, long sTime, int processID){    
    if(sTime > speed3 * 1000000000){
        sTime = sTime - (speed3 * 1000000000);
        cout << sTime << ":Processor 3";
        cout << " Process ID: " << processID << "\n";
        return data(speed3, sTime, processID);
    }
    else{
        cout << 0 << ":Processor 3";
        cout << " Process ID: " << processID << "\n";
        return data(speed3, 0, processID);

    }
}