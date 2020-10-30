#include "processor4.h"
#include "struct.h"

data processor4(long speed4, long sTime, int processID){    
    if(sTime > speed4 * 1000000000){
        sTime = sTime - (speed4 * 1000000000);
        cout << sTime << ":Processor 4";
        cout << " Process ID: " << processID << "\n";
        return data(speed4, sTime, processID);
    }
    else{
        cout << 0 << ":Processor 4";
        cout << " Process ID: " << processID << "\n";
        return data(speed4, 0, processID);
    }
}
