#include "processor1.h"
#include "struct.h"

data processor1(long speed1, long sTime, int processID){    
    if(sTime > speed1 * 1000000000){
        sTime = sTime - (speed1 * 1000000000);
        cout << sTime << ":Processor 1";
        cout << " Process ID: " << processID << "\n";
        return data(speed1, sTime, processID);
    }
    else{
        cout << 0 << ":Processor 1";
        cout << " Process ID: " << processID << "\n";
        return data(speed1, 0, processID);
    }
}     


/*
        long fraction = sTime/(speed1 * 1000000000);
        sTime = sTime - sTime;
        cout << sTime << ":Processor 1\n";
        //return temp(sTime, true); 
        */