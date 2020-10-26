#include <queue>
#include <unistd.h>
using namespace std;
bool processorFull1 = false;
bool processorFull2 = false;
bool processorFull3 = false;
bool processorFull4 = false;


struct node{ //Struct to store the two random values in a container
    node(long s, int m) : serviceTime(s), memorySize(m){}
    long serviceTime;
    int memorySize;
};

void processor1(int speed1, int sTime){
    processorFull1 = true;
    while(sTime != 0){
        if(sTime > speed1 * 1,000,000,000){
            usleep(1000000);
            sTime = sTime - speed1 * 1,000,000,000;
        }   
        else{
            int fraction = sTime/(speed1 * 1,000,000,000);
            usleep(fraction * 1000000);
            sTime = sTime - sTime;
        }
    }
    processorFull1 = false;

}

void processor2(int speed2, int sTime){
    processorFull2 = true;
    while(sTime != 0){
        if(sTime > speed2 * 1,000,000,000){
            usleep(1000000);
            sTime = sTime - speed2 * 1,000,000,000;
        }   
        else{
            int fraction = sTime/(speed2 * 1,000,000,000);
            usleep(fraction * 1000000);
            sTime = sTime - sTime;
        }
    }
    processorFull1 = false;
}

void processor3(int speed3, int sTime){
    processorFull3 = true;
    while(sTime != 0){
        if(sTime > speed3 * 1,000,000,000){
            usleep(1000000);
            sTime = sTime - speed3 * 1,000,000,000;
        }   
        else{
            int fraction = sTime/(speed3 * 1,000,000,000);
            usleep(fraction * 1000000);
            sTime = sTime - sTime;
        }
    }
    processorFull1 = false;
}

void processor4(int speed4, int sTime){
    while(sTime != 0){
        if(sTime > speed4 * 1,000,000,000){
            usleep(1000000);
            sTime = sTime - speed4 * 1,000,000,000;
        }   
        else{
            int fraction = sTime/(speed4 * 1,000,000,000);
            usleep(fraction * 1000000);
            sTime = sTime - sTime;
        }
    }
    processorFull1 = false;
}

void FIFO(queue<node> processes, int speed1, int speed2, int speed3, int speed4, int memory1, int memory2, int memory3, int memory4){
    while(!processes.empty()){
        node temp = processes.front();
        int processServiceTime = temp.serviceTime;
        int processMemorySize = temp.memorySize;
        processes.pop();

        if(processorFull1 == false){
            if(processMemorySize <= memory1){
                processor1(speed1, processServiceTime);
            }
        }
        else if(processorFull2 == false){
          if(processMemorySize <= memory2){
                processor2(speed2, processServiceTime);
            } 
        }
        else if(processorFull3 == false){
            if(processMemorySize <= memory3){
                processor2(speed3, processServiceTime);
            }
        }
        else if(processorFull4 == false){
            if(processMemorySize >= memory4){
                processor2(speed4, processServiceTime);
            }
        }
        else{

        }
    }
}

