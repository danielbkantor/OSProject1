//Daniel Kantor & Derek Levine
#include "FIFO.h"
#include "processor1.h"
#include "processor2.h"
#include "processor3.h"
#include "processor4.h"
#include "struct.h"
#include <fstream>

bool processorFull1 = false;
bool processorFull2 = false;
bool processorFull3 = false;
bool processorFull4 = false;
bool finish1 = false;
bool finish2 = false;
bool finish3 = false;
bool finish4 = false;
data temp1(0,0,0,0);
data temp2(0,0,0,0);
data temp3(0,0,0,0);
data temp4(0,0,0,0);
queue<node> fourGB;
queue<node> eightGB;
queue<int> IDNumber;
queue<long> outputServiceTime;
queue<int> outMem;
queue<long> waitTime;
queue<long> outTotalTime;
long totalTurnaround = 0;


void FIFO(queue<node> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4, int scenario){
    while(processes.empty() == false|| fourGB.empty() == false|| eightGB.empty() == false){
        if(processorFull1 == true && processorFull2 == true && processorFull3 == true && processorFull4 == true){
            if(temp1.remainingServiceTime > 0){
                    temp1 = processor1(speed1, temp1.remainingServiceTime, temp1.processID, temp1.serviceTime);  
            } 
            if(temp1.remainingServiceTime == 0){
                totalTurnaround = totalTurnaround + temp1.serviceTime;
                temp2.serviceTime = temp2.serviceTime - temp1.serviceTime;
                temp3.serviceTime = temp3.serviceTime - temp1.serviceTime;
                temp4.serviceTime = temp4.serviceTime - temp1.serviceTime;
                processorFull1 = false;
                continue;
            }
            
            if(temp2.remainingServiceTime > 0){
                temp2 = processor2(speed2, temp2.remainingServiceTime, temp2.processID, temp2.serviceTime);
            }
            if(temp2.remainingServiceTime == 0){
                totalTurnaround = totalTurnaround + temp2.serviceTime;
                temp1.serviceTime = temp1.serviceTime - temp2.serviceTime;
                temp3.serviceTime = temp3.serviceTime - temp2.serviceTime;
                temp4.serviceTime = temp4.serviceTime - temp2.serviceTime;
                processorFull2 = false;
                continue;
            }
            if(temp3.remainingServiceTime > 0){
                temp3 = processor3(speed3, temp3.remainingServiceTime, temp3.processID, temp3.serviceTime);
            }
            if(temp3.remainingServiceTime == 0){
                totalTurnaround = totalTurnaround + temp3.serviceTime;
                temp1.serviceTime = temp1.serviceTime - temp3.serviceTime;
                temp2.serviceTime = temp2.serviceTime - temp3.serviceTime;
                temp4.serviceTime = temp4.serviceTime - temp3.serviceTime;
                processorFull3 = false;
                continue;
            }
            if(temp4.remainingServiceTime > 0){
                temp4 = processor4(speed4, temp4.remainingServiceTime, temp4.processID, temp4.serviceTime);
            }
            if(temp4.remainingServiceTime == 0){
                totalTurnaround = totalTurnaround + temp4.serviceTime;
                temp1.serviceTime = temp1.serviceTime - temp4.serviceTime;
                temp2.serviceTime = temp2.serviceTime - temp4.serviceTime;
                temp3.serviceTime = temp3.serviceTime - temp4.serviceTime;
                processorFull4 = false;
                continue;
            }
        }
        else if(processorFull1 == false){//If Proccessor1 is empty it will pop a process from the queue
            node temp = processes.front();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory1){//process will run if it only requires less than 2GB
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                IDNumber.push(ID);
                outputServiceTime.push(processServiceTime);
                outMem.push(processMemorySize);
                waitTime.push(totalTurnaround);
                long totalTime = totalTurnaround + processServiceTime;
                outTotalTime.push(totalTime);
                processes.pop();
                processorFull1 = true;
                if(temp.serviceTime != 0){
                    temp1 = processor1(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{
                if(processMemorySize > 2 && processMemorySize < 5){//If processes require more than 2GB they will be placed into their repsective queues 
                    fourGB.push(temp);
                    processes.pop();
                }
                else{
                    eightGB.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull2 == false){//If Proccessor2 is empty it will pop a process from the queue
            node temp = processes.front();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory2){//process will run if it only requires less than 2GB
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                IDNumber.push(ID);
                outputServiceTime.push(processServiceTime);
                outMem.push(processMemorySize);
                waitTime.push(totalTurnaround);
                long totalTime = totalTurnaround + processServiceTime;
                outTotalTime.push(totalTime);
                processes.pop();
                processorFull2 = true;
                if(temp.serviceTime != 0){
                    temp2 = processor2(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{
                if(processMemorySize > 2 && processMemorySize < 5){//If processes require more than 2GB they will be placed into their repsective queues 
                    fourGB.push(temp);
                    processes.pop();
                }
                else{
                    eightGB.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull3 == false){//Proccessor3 is empty it will pop a process from the 4GB queue
            if(fourGB.empty() == false){
                node temp = fourGB.front();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory3){//process will run if it only requires less than 4GB
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumber.push(ID);
                    outputServiceTime.push(processServiceTime);
                    outMem.push(processMemorySize);
                    waitTime.push(totalTurnaround);
                    long totalTime = totalTurnaround + processServiceTime;
                    outTotalTime.push(totalTime);
                    fourGB.pop();
                    processorFull3 = true;
                    temp3 = processor3(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{//If 4GB queue is empty than it take from the processes queue
                node temp = processes.front();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory3){
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumber.push(ID);
                    outputServiceTime.push(processServiceTime);
                    outMem.push(processMemorySize);
                    waitTime.push(totalTurnaround);
                    long totalTime = totalTurnaround + processServiceTime;
                    outTotalTime.push(totalTime);
                    processes.pop();
                    processorFull3 = true;
                    if(temp.serviceTime != 0){
                        temp3 = processor3(0, processServiceTime, ID, processServiceTime);
                    }
                }
                else{
                    eightGB.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull4 == false){// 8 GB
            if(eightGB.empty() == false){
                node temp = eightGB.front();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory4){
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumber.push(ID);
                    outputServiceTime.push(processServiceTime);
                    outMem.push(processMemorySize);
                    waitTime.push(totalTurnaround);
                    long totalTime = totalTurnaround + processServiceTime;
                    outTotalTime.push(totalTime);
                    eightGB.pop();
                    processorFull4 = true;
                    temp4 = processor4(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{
                node temp = processes.front();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory4){
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumber.push(ID);
                    outputServiceTime.push(processServiceTime);
                    outMem.push(processMemorySize);
                    waitTime.push(totalTurnaround);
                    long totalTime = totalTurnaround + processServiceTime;
                    outTotalTime.push(totalTime);
                    processes.pop();
                    processorFull4 = true;
                    if(temp.serviceTime != 0){
                        temp4 = processor4(0, processServiceTime, ID, processServiceTime);
                    }
                }
            }
        }
    }
    // Will continue running all the processes left on the processors after the queue is empty. Will run until athe processes finish
    while(temp1.remainingServiceTime > 0 || temp2.remainingServiceTime > 0 || temp3.remainingServiceTime > 0 || temp4.remainingServiceTime > 0){
        if(temp1.remainingServiceTime > 0){
            temp1 = processor1(speed1, temp1.remainingServiceTime, temp1.processID, temp1.serviceTime);
        }
        else if(finish1 == false){
            totalTurnaround = totalTurnaround + temp1.serviceTime;
            temp2.serviceTime = temp2.serviceTime - temp1.serviceTime;
            temp3.serviceTime = temp3.serviceTime - temp1.serviceTime;
            temp4.serviceTime = temp4.serviceTime - temp1.serviceTime;
            finish1 = true;
        }
        if(temp2.remainingServiceTime > 0){
            temp2 = processor2(speed2, temp2.remainingServiceTime, temp2.processID, temp2.serviceTime);
        }
        else if(finish2 == false){
            totalTurnaround = totalTurnaround + temp2.serviceTime;
            temp1.serviceTime = temp1.serviceTime - temp2.serviceTime;
            temp3.serviceTime = temp3.serviceTime - temp2.serviceTime;
            temp4.serviceTime = temp4.serviceTime - temp2.serviceTime;   
            finish2 = true;
        }
        if(temp3.remainingServiceTime > 0){
           temp3 = processor3(speed3, temp3.remainingServiceTime, temp3.processID,temp3.serviceTime);   
        }
        else if(finish3 == false){
            totalTurnaround = totalTurnaround + temp3.serviceTime;
            temp1.serviceTime = temp1.serviceTime - temp3.serviceTime;
            temp2.serviceTime = temp2.serviceTime - temp3.serviceTime;
            temp4.serviceTime = temp4.serviceTime - temp3.serviceTime;
            finish3 = true;
        }
        if(temp4.remainingServiceTime > 0){
            temp4 = processor4(speed4, temp4.remainingServiceTime, temp4.processID, temp4.serviceTime);
        }
        else if(finish4 == false){
            totalTurnaround = totalTurnaround + temp4.serviceTime;
            temp1.serviceTime = temp1.serviceTime - temp4.serviceTime;
            temp2.serviceTime = temp2.serviceTime - temp4.serviceTime;
            temp3.serviceTime = temp3.serviceTime - temp4.serviceTime;
            finish4 = true;
        }
    }
    
    ofstream results("FIFO.txt");
    results << "Scenario " << scenario << " \n";
    results << "Total Turnaround time is " << totalTurnaround  << " cycles \n";
    int i = 0;
    long avgWaitTime = 0;
    long avgTurnTime = 0;
    while(i < 40){
        results << "\n";
        results << "ID Number: " << IDNumber.front() << "\n";
        results << "Service Time: " << outputServiceTime.front() << " cycles\n";
        results << "Memory Requirements: " << outMem.front() << "GB \n";
        results << "Wait Time: " << waitTime.front() << " cycles \n";
        results << "Total Time: " << outTotalTime.front() << " cycles \n";
        avgWaitTime = avgWaitTime + waitTime.front();
        avgTurnTime = avgTurnTime + outTotalTime.front();
        IDNumber.pop();
        outputServiceTime.pop();
        outMem.pop();
        waitTime.pop();
        outTotalTime.pop();
        i++;
    }
    results << "\n";
    avgWaitTime = avgWaitTime/40;
    results << "Average wait time is: " << avgWaitTime << " cycles \n";
    avgTurnTime = avgTurnTime/40;
    results << "Average turnaround time is: " << avgTurnTime << " cycles";
    results.close();
}





