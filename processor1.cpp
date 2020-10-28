#include "processor1.h"

void processor1(long speed1, long sTime){
    while(sTime != 0){
        if(sTime > speed1 * 1000000000){
            usleep(1000000);
            sTime = sTime - (speed1 * 1000000000);
            cout << sTime << ":Processor 1\n";
        }   
        else{
            long fraction = sTime/(speed1 * 1000000000);
            usleep(fraction * 1000000);
            sTime = sTime - sTime;
            cout << sTime << ":Processor 1\n";
        }
    }
}