//Daniel Kantor & Derek Levine
#include "processor1.h"
#include "struct.h"

data processor1(long speed1, long sTime, int processID, long serviceTime){    
    if(sTime > speed1 * 1000000000){//if the service time of the process is greater than 1 billion * speed (simulating speed of CPU which is 1 billion * #GHz) then it subtracts 1 billion * speed
        sTime = sTime - (speed1 * 1000000000);
        cout << sTime << ":Processor 1";
        cout << " Process ID: " << processID << "\n";
        return data(speed1, sTime, processID, serviceTime); //returns the remaining service time left
    }
    else{
        cout << 0 << ":Processor 1";//if service time of the process is less than 1 billion * speed then the service time left will be 0, so it returns 0 and the process is done.
        cout << " Process ID: " << processID << "\n";
        return data(speed1, 0, processID, serviceTime);
    }
}     


/*
        long fraction = sTime/(speed1 * 1000000000);
        sTime = sTime - sTime;
        cout << sTime << ":Processor 1\n";
        //return temp(sTime, true); 
        */