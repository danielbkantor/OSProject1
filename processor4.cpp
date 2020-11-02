//Daniel Kantor & Derek Levine
#include "processor4.h"
#include "struct.h"

data processor4(long speed4, long sTime, int processID, long serviceTime){
    if(sTime > speed4 * 1000000000){//if the service time of the process is greater than 1 billion * speed (simulating speed of CPU which is 1 billion * #GHz) then it subtracts 1 billion * speed
        sTime = sTime - (speed4 * 1000000000);
        cout << sTime << ":Processor 4";
        cout << " Process ID: " << processID << "\n";
        return data(speed4, sTime, processID,  serviceTime); //returns the remaining service time left
    }
    else{
        cout << 0 << ":Processor 4";//if service time of the process is less than 1 billion * speed then the service time left will be 0, so it returns 0 and the process is done.
        cout << " Process ID: " << processID << "\n";
        return data(speed4, 0, processID, serviceTime);
    }
}
