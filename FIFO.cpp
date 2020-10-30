#include "FIFO.h"
#include "processor1.h"
#include "processor2.h"
#include "processor3.h"
#include "processor4.h"
#include "struct.h"



bool processorFull1 = false;
bool processorFull2 = false;
bool processorFull3 = false;
bool processorFull4 = false;
data temp1(0,0,0);
data temp2(0,0,0);
data temp3(0,0,0);
data temp4(0,0,0);




void FIFO(queue<node> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4){
    while(!processes.empty()){
        if(processorFull1 == true && processorFull2 == true && processorFull3 == true && processorFull4 == true){
            if(temp1.remainingServiceTime > 0){
                temp1 = processor1(speed1, temp1.remainingServiceTime, temp1.processID);
            }
            else{
                processorFull1 = false;
            }
            if(temp2.remainingServiceTime > 0){
                temp2 = processor2(speed2, temp2.remainingServiceTime, temp2.processID);
            }
            else{
                processorFull2 = false;
            }
            if(temp3.remainingServiceTime > 0){
                temp3 = processor3(speed3, temp3.remainingServiceTime, temp3.processID);
            }
            else{
                processorFull3 = false;
            }
            if(temp4.remainingServiceTime > 0){
                temp4 = processor4(speed4, temp4.remainingServiceTime, temp4.processID);
            }
            else{
                processorFull4 = false;
            }
        }
        else if(processorFull1 == false){
            node temp = processes.front();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory1){
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                processes.pop();
                processorFull1 = true;
                temp1 = processor1(speed1, processServiceTime, ID);
            }
        }
        else if(processorFull2 == false){
            node temp = processes.front();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory2){
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                processes.pop();
                processorFull2 = true;
                temp2 = processor2(speed2, processServiceTime, ID);
            }
        }
        else if(processorFull3 == false){
            node temp = processes.front();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory3){
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                processes.pop();
                processorFull3 = true;
                temp3 = processor3(speed3, processServiceTime, ID);
            }
        }
        else if(processorFull4 == false){
            node temp = processes.front();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory4){
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                processes.pop();
                processorFull4 = true;
                temp4 = processor4(speed4, processServiceTime, ID);
            }
        }
    }
    while(temp1.remainingServiceTime > 0 || temp2.remainingServiceTime > 0 || temp3.remainingServiceTime > 0 || temp4.remainingServiceTime > 0){
        if(temp1.remainingServiceTime > 0){
            temp1 = processor1(speed1, temp1.remainingServiceTime, temp1.processID);
        }
        if(temp2.remainingServiceTime > 0){
            temp2 = processor2(speed2, temp2.remainingServiceTime, temp2.processID);
        }
        if(temp3.remainingServiceTime > 0){
            temp3 = processor3(speed3, temp3.remainingServiceTime, temp3.processID);
        }
        if(temp4.remainingServiceTime > 0){
            temp4 = processor4(speed4, temp4.remainingServiceTime, temp4.processID);
        }
    }
}




