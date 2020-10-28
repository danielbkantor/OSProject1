#include "processor2.h"


void processor2(long speed2, long sTime){
    while(sTime != 0){
        if(sTime > speed2 * 1000000000){
            usleep(1000000);
            sTime = sTime - speed2 * 1000000000;
            cout << sTime << ":Processor 2\n";

        }   
        else{
            int fraction = sTime/(speed2 * 1000000000);
            usleep(fraction * 1000000);
            sTime = sTime - sTime;
            cout << sTime << ":Processor 2\n";

        }
    }
}
