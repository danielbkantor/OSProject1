#include "processor4.h"

void processor4(long speed4, long sTime){    
    while(sTime != 0){
        if(sTime > speed4 * 1000000000){
            usleep(1000000);
            sTime = sTime - speed4 * 1000000000;
            cout << sTime << ":Processor 4\n";

        }   
        else{
            int fraction = sTime/(speed4 * 1000000000);
            usleep(fraction * 1000000);
            sTime = sTime - sTime;
            cout << sTime << ":Processor 4\n";

        }
    }
}