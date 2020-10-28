#include "processor3.h"


void processor3(long speed3, long sTime){
    while(sTime != 0){
        if(sTime > speed3 * 1000000000){
            usleep(1000000);
            sTime = sTime - speed3 * 1000000000;
            cout << sTime << ":Processor 3\n";

        }   
        else{
            int fraction = sTime/(speed3 * 1000000000);
            usleep(fraction * 1000000);
            sTime = sTime - sTime;
            cout << sTime << ":Processor 3\n";

        }
    }
}