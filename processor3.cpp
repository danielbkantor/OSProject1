//Daniel Kantor & Derek Levine
#include "processor3.h"
#include "struct.h"

data processor3(long speed3, long sTime, int processID, long serviceTime){    
    if(sTime > speed3 * 1000000000){//if the service time of the process is greater than 1 billion * speed (simulating speed of CPU which is 1 billion * #GHz) then it subtracts 1 billion * speed
        sTime = sTime - (speed3 * 1000000000);
        cout << sTime << ":Processor 3";
        cout << " Process ID: " << processID << "\n";
        return data(speed3, sTime, processID,serviceTime);//returns the remaining service time left
    }
    else{
        cout << 0 << ":Processor 3"; //if service time of the process is less than 1 billion * speed then the service time left will be 0, so it returns 0 and the process is done.
        cout << " Process ID: " << processID << "\n";
        return data(speed3, 0, processID, serviceTime);

    }
}