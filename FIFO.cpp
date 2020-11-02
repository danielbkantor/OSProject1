//Daniel Kantor & Derek Levine
#include "FIFO.h"
#include "processor1.h"
#include "processor2.h"
#include "processor3.h"
#include "processor4.h"
#include "struct.h"
#include <fstream>
//varibles to keep track if proccesors are full
bool processorFull1 = false;
bool processorFull2 = false;
bool processorFull3 = false;
bool processorFull4 = false;
//variables to keep track if the last four processes in the system are completed, to keep track of turnaround time
bool finish1 = false;
bool finish2 = false;
bool finish3 = false;
bool finish4 = false;
//the structs that we pass to the processors so the processes can be worked on
data temp1(0,0,0,0);
data temp2(0,0,0,0);
data temp3(0,0,0,0);
data temp4(0,0,0,0);
//if a process is too large to enter a given processor, it will enter a queue to be assigned to a processor with more memory
queue<node> fourGB;
queue<node> eightGB;
//queues to keep track of data to be output to a file at end of execution
queue<int> IDNumber;
queue<long> outputServiceTime;
queue<int> outMem;
queue<long> waitTime;
queue<long> outTotalTime;
long totalTurnaround = 0;

//FIFO method, is where the scheduling occurs. 
void FIFO(queue<node> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4, int scenario){
    while(processes.empty() == false|| fourGB.empty() == false|| eightGB.empty() == false){//will continue running while one these queues have something in them
        if(processorFull1 == true && processorFull2 == true && processorFull3 == true && processorFull4 == true){//if all the processors are full then all the processes will run
                                                                                                                //if all are not full, then all processes will stop execution and add a processes will be loaded onto free processor
            if(temp1.remainingServiceTime > 0){//run until process is done
                    temp1 = processor1(speed1, temp1.remainingServiceTime, temp1.processID, temp1.serviceTime);  
            } 
            if(temp1.remainingServiceTime == 0){//used to figure out turnaround time of the system
                totalTurnaround = totalTurnaround + temp1.serviceTime;
                temp2.serviceTime = temp2.serviceTime - temp1.serviceTime;
                temp3.serviceTime = temp3.serviceTime - temp1.serviceTime;
                temp4.serviceTime = temp4.serviceTime - temp1.serviceTime;
                processorFull1 = false;//signal process is done
                continue;
            }
            
            if(temp2.remainingServiceTime > 0){//run until process is done
                temp2 = processor2(speed2, temp2.remainingServiceTime, temp2.processID, temp2.serviceTime);
            }
            if(temp2.remainingServiceTime == 0){//used to figure out turnaround time of the system
                totalTurnaround = totalTurnaround + temp2.serviceTime;
                temp1.serviceTime = temp1.serviceTime - temp2.serviceTime;
                temp3.serviceTime = temp3.serviceTime - temp2.serviceTime;
                temp4.serviceTime = temp4.serviceTime - temp2.serviceTime;
                processorFull2 = false;//signal process is done
                continue;
            }
            if(temp3.remainingServiceTime > 0){//run until process is done
                temp3 = processor3(speed3, temp3.remainingServiceTime, temp3.processID, temp3.serviceTime);
            }
            if(temp3.remainingServiceTime == 0){//used to figure out turnaround time of the system
                totalTurnaround = totalTurnaround + temp3.serviceTime;
                temp1.serviceTime = temp1.serviceTime - temp3.serviceTime;
                temp2.serviceTime = temp2.serviceTime - temp3.serviceTime;
                temp4.serviceTime = temp4.serviceTime - temp3.serviceTime;
                processorFull3 = false;//signal process is done
                continue;
            }
            if(temp4.remainingServiceTime > 0){//run until process is done
                temp4 = processor4(speed4, temp4.remainingServiceTime, temp4.processID, temp4.serviceTime);
            }
            if(temp4.remainingServiceTime == 0){//used to figure out turnaround time of the system
                totalTurnaround = totalTurnaround + temp4.serviceTime;
                temp1.serviceTime = temp1.serviceTime - temp4.serviceTime;
                temp2.serviceTime = temp2.serviceTime - temp4.serviceTime;
                temp3.serviceTime = temp3.serviceTime - temp4.serviceTime;
                processorFull4 = false;//signal process is done
                continue;
            }
        }
        else if(processorFull1 == false){//if processor 1 is empty then get the process at the top of the queue
            node temp = processes.front();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory1){//if the memory of the process fits the memory of the processes put the process onto the processor and then remove the process from the queue
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                IDNumber.push(ID);
                outputServiceTime.push(processServiceTime);
                outMem.push(processMemorySize);
                waitTime.push(totalTurnaround);
                long totalTime = totalTurnaround + processServiceTime;
                outTotalTime.push(totalTime);
                processes.pop();
                processorFull1 = true;//signal that the processor is now running a process
                if(temp.serviceTime != 0){
                    temp1 = processor1(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{//if the process is too large for the memeory size of the processor, it will push it to the appropiate queue for the processor that has enough size
                if(processMemorySize > 2 && processMemorySize < 5){
                    fourGB.push(temp);
                    processes.pop();
                }
                else{
                    eightGB.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull2 == false){// if processor 2 is empty, then get the process at the top of the queue
            node temp = processes.front();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory2){//if the memory of the process fits the memory of the processes put the process onto the processor and then remove the process from the queue
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                IDNumber.push(ID);
                outputServiceTime.push(processServiceTime);
                outMem.push(processMemorySize);
                waitTime.push(totalTurnaround);
                long totalTime = totalTurnaround + processServiceTime;
                outTotalTime.push(totalTime);
                processes.pop();
                processorFull2 = true;//signal that a processor is now running a process
                if(temp.serviceTime != 0){
                    temp2 = processor2(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{//if the process is too large for the memeory size of the processor, it will push it to the appropiate queue for the processor that has enough size and remove it from the processes queue
                if(processMemorySize > 2 && processMemorySize < 5){ 
                    fourGB.push(temp);
                    processes.pop();
                }
                else{
                    eightGB.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull3 == false){//check if processor 3 is empty
            if(fourGB.empty() == false){//if there are any processes that need to run on the 4GB memory processor then take it from that queue
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
                    processorFull3 = true;//signal that a processor is now running a process
                    temp3 = processor3(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{//if there aren't any processes waiting from in the 4GB queue then take one from the processes queue and put it on the processor
                node temp = processes.front();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory3){//if the memory of the process fits the memory of the processes put the process onto the processor and then remove the process from the queue
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumber.push(ID);
                    outputServiceTime.push(processServiceTime);
                    outMem.push(processMemorySize);
                    waitTime.push(totalTurnaround);
                    long totalTime = totalTurnaround + processServiceTime;
                    outTotalTime.push(totalTime);
                    processes.pop();
                    processorFull3 = true;//signal that a processor is now running a process
                    if(temp.serviceTime != 0){
                        temp3 = processor3(0, processServiceTime, ID, processServiceTime);
                    }
                }
                else{//if the memory of the process is too large for this processor, then put it on the 8GB queue and remove it from processe queue
                    eightGB.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull4 == false){//check if processor4 is empty
            if(eightGB.empty() == false){// if there are any processes in the 8GB queue, then remove that process from the queue and put it to run on the processor
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
                    processorFull4 = true;//signal that a processor is now running a process
                    temp4 = processor4(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{//if there are no processes in the 8GB queue, take a process from the processor queue and put it on the CPU to execute
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
                    processorFull4 = true;//signal that a processor is now running a process
                    if(temp.serviceTime != 0){
                        temp4 = processor4(0, processServiceTime, ID, processServiceTime);
                    }
                }
            }
        }
    }
    //Once the queues are empty, the while loop above will continue running. However, there still could be processes that haven't finished running. 
    //This ensures that the processes remaining on the processors will run until completion    
    while(temp1.remainingServiceTime > 0 || temp2.remainingServiceTime > 0 || temp3.remainingServiceTime > 0 || temp4.remainingServiceTime > 0){
        if(temp1.remainingServiceTime > 0){//if process on processor1 has service time left, run
            temp1 = processor1(speed1, temp1.remainingServiceTime, temp1.processID, temp1.serviceTime);
        }
        else if(finish1 == false){//flag as finished running, in order to handle total turnaround time calculation
            totalTurnaround = totalTurnaround + temp1.serviceTime;
            temp2.serviceTime = temp2.serviceTime - temp1.serviceTime;
            temp3.serviceTime = temp3.serviceTime - temp1.serviceTime;
            temp4.serviceTime = temp4.serviceTime - temp1.serviceTime;
            finish1 = true;
        }
        if(temp2.remainingServiceTime > 0){//if process on processor2 has service time left, run
            temp2 = processor2(speed2, temp2.remainingServiceTime, temp2.processID, temp2.serviceTime);
        }
        else if(finish2 == false){//flag as finished running, in order to handle total turnaround time calculation
            totalTurnaround = totalTurnaround + temp2.serviceTime;
            temp1.serviceTime = temp1.serviceTime - temp2.serviceTime;
            temp3.serviceTime = temp3.serviceTime - temp2.serviceTime;
            temp4.serviceTime = temp4.serviceTime - temp2.serviceTime;   
            finish2 = true;
        }
        if(temp3.remainingServiceTime > 0){//if process on processor4 has service time left, run
           temp3 = processor3(speed3, temp3.remainingServiceTime, temp3.processID,temp3.serviceTime);   
        }
        else if(finish3 == false){//flag as finished running, in order to handle total turnaround time calculation
            totalTurnaround = totalTurnaround + temp3.serviceTime;
            temp1.serviceTime = temp1.serviceTime - temp3.serviceTime;
            temp2.serviceTime = temp2.serviceTime - temp3.serviceTime;
            temp4.serviceTime = temp4.serviceTime - temp3.serviceTime;
            finish3 = true;
        }
        if(temp4.remainingServiceTime > 0){//if process on processor4 has service time left, run
            temp4 = processor4(speed4, temp4.remainingServiceTime, temp4.processID, temp4.serviceTime);
        }
        else if(finish4 == false){//flag as finished running, in order to handle total turnaround time calculation
            totalTurnaround = totalTurnaround + temp4.serviceTime;
            temp1.serviceTime = temp1.serviceTime - temp4.serviceTime;
            temp2.serviceTime = temp2.serviceTime - temp4.serviceTime;
            temp3.serviceTime = temp3.serviceTime - temp4.serviceTime;
            finish4 = true;
        }
    }
    //The code used to output all the data collected to a file called results.txt
    ofstream results("results.txt");
    results << "Scenario " << scenario << " \n";
    results << "Total Turnaround time is " << totalTurnaround  << " cycles \n";
    int i = 0;
    long avgWaitTime = 0;
    long avgTurnTime = 0;
    long avgServTime = 0;
    double avgmemSize = 0;
    while(i < 40){
        results << "\n";
        results << "ID Number: " << IDNumber.front() << "\n";
        results << "Service Time: " << outputServiceTime.front() << " cycles\n";
        results << "Memory Requirements: " << outMem.front() << "GB \n";
        results << "Wait Time: " << waitTime.front() << " cycles \n";
        results << "Total Time: " << outTotalTime.front() << " cycles \n";
        avgWaitTime = avgWaitTime + waitTime.front();
        avgTurnTime = avgTurnTime + outTotalTime.front();
        avgServTime = avgServTime + outputServiceTime.front();
        avgmemSize = avgmemSize + outMem.front();
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
    results << "Average turnaround time is: " << avgTurnTime << " cycles\n";
    avgServTime = avgServTime/40;
    results << "Average service time is: " << avgServTime << " cycles\n";
    avgmemSize = avgmemSize/40;
    results << "Average memory size is: " << avgmemSize << "GB";

    results.close();
}





