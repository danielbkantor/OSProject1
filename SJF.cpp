//Daniel Kantor & Derek Levine
#include "SJF.h"
#include "processor1.h"
#include "processor2.h"
#include "processor3.h"
#include "processor4.h"
#include "struct.h"
#include <fstream>
//varibles to keep track if proccesors are full
bool processorFull1SJF = false;
bool processorFull2SJF = false;
bool processorFull3SJF = false;
bool processorFull4SJF = false;
//variables to keep track if the last four processes in the system are completed, to keep track of turnaround time
bool finish1SJF = false;
bool finish2SJF = false;
bool finish3SJF = false;
bool finish4SJF = false;
//the structs that we pass to the processors so the processes can be worked on
data temp1SJF(0,0,0,0);
data temp2SJF(0,0,0,0);
data temp3SJF(0,0,0,0);
data temp4SJF(0,0,0,0);
//if a process is too large to enter a given processor, it will enter a queue to be assigned to a processor with more memory
priority_queue<priorityNode> fourGBSJF;
priority_queue<priorityNode> eightGBSJF;
//queues to keep track of data to be output to a file at end of execution
queue<int> IDNumberSJF;
queue<long> outputServiceTimeSJF;
queue<int> outMemSJF;
queue<long> waitTimeSJF;
queue<long> outTotalTimeSJF;
long totalTurnaroundSJF = 0;

//SJF method, is where the scheduling occurs 
void SJF(priority_queue<priorityNode> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4, int scenario){
    while(!processes.empty() || !fourGBSJF.empty() || !eightGBSJF.empty()){//will run until all the queues are empty
        if(processorFull1SJF == true && processorFull2SJF == true && processorFull3SJF == true && processorFull4SJF == true){//if all the processors are full, the processes will continue doing work until one finishes
                                                                                                                    //if all are not full, then all processes will stop execution and add a processes will be loaded onto free processor
            if(temp1SJF.remainingServiceTime > 0){//run until process is done
                temp1SJF = processor1(speed1, temp1SJF.remainingServiceTime, temp1SJF.processID, temp1SJF.serviceTime);
            }
            else{
                totalTurnaroundSJF = totalTurnaroundSJF + temp1SJF.serviceTime;//used to figure out the turnaround time of system
                temp2SJF.serviceTime = temp2SJF.serviceTime - temp1SJF.serviceTime;
                temp3SJF.serviceTime = temp3SJF.serviceTime - temp1SJF.serviceTime;
                temp4SJF.serviceTime = temp4SJF.serviceTime - temp1SJF.serviceTime;
                processorFull1SJF = false;//signal process is done
                continue;
            }
            if(temp2SJF.remainingServiceTime > 0){//run until the process finishes
                temp2SJF = processor2(speed2, temp2SJF.remainingServiceTime, temp2SJF.processID, temp2SJF.serviceTime);
            }  
            else{
                totalTurnaroundSJF = totalTurnaroundSJF + temp2SJF.serviceTime;//used to figure out the turnaround time of system
                temp1SJF.serviceTime = temp1SJF.serviceTime - temp2SJF.serviceTime;
                temp3SJF.serviceTime = temp3SJF.serviceTime - temp2SJF.serviceTime;
                temp4SJF.serviceTime = temp4SJF.serviceTime - temp2SJF.serviceTime;
                processorFull2SJF = false;//signal process is done
                continue;
            }
            if(temp3SJF.remainingServiceTime > 0){//run until the process finishes
                temp3SJF = processor3(speed3, temp3SJF.remainingServiceTime, temp3SJF.processID, temp3SJF.serviceTime);
            }
            else{
                totalTurnaroundSJF = totalTurnaroundSJF + temp3SJF.serviceTime;//used to figure out the turnaround time of system
                temp1SJF.serviceTime = temp1SJF.serviceTime - temp3SJF.serviceTime;
                temp2SJF.serviceTime = temp2SJF.serviceTime - temp3SJF.serviceTime;
                temp4SJF.serviceTime = temp4SJF.serviceTime - temp3SJF.serviceTime;
                processorFull3SJF = false;//signal process is done
                continue;
            }
            if(temp4SJF.remainingServiceTime > 0){//run until the process finishes
                temp4SJF = processor4(speed4, temp4SJF.remainingServiceTime, temp4SJF.processID, temp4SJF.serviceTime);
            }   
            else{
                totalTurnaroundSJF = totalTurnaroundSJF + temp4SJF.serviceTime;//used to figure out the turnaround time of system
                temp1SJF.serviceTime = temp1SJF.serviceTime - temp4SJF.serviceTime;
                temp2SJF.serviceTime = temp2SJF.serviceTime - temp4SJF.serviceTime;
                temp3SJF.serviceTime = temp3SJF.serviceTime - temp4SJF.serviceTime;
                processorFull4SJF = false;//signal process is done
                continue;
            }
        }
        else if(processorFull1SJF == false){//if processor 1 is empty then get the process at the top of the queue
            priorityNode temp = processes.top();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory1){//if the memory of the process fits the memory of the processes put the process onto the processor and then remove the process from the queue
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                IDNumberSJF.push(ID);
                outputServiceTimeSJF.push(processServiceTime);
                outMemSJF.push(processMemorySize);
                waitTimeSJF.push(totalTurnaroundSJF);
                long totalTime = totalTurnaroundSJF + processServiceTime;
                outTotalTimeSJF.push(totalTime);
                processes.pop();
                processorFull1SJF = true;//signal that the processor is now running a process
                if(temp.serviceTime !=0){
                   temp1SJF = processor1(0, processServiceTime, ID, processServiceTime); 
                }
            }
            else{//if the process is too large for the memeory size of the processor, it will push it to the appropiate queue for the processor that has enough size
                if(processMemorySize > 2 && processMemorySize < 5){
                    fourGBSJF.push(temp);
                    processes.pop();
                }
                else{
                    eightGBSJF.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull2SJF == false){// if processor 2 is empty, then get the process at the top of the queue
            priorityNode temp = processes.top();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory2){//if the memory of the process fits the memory of the processes put the process onto the processor and then remove the process from the queue
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                IDNumberSJF.push(ID);
                outputServiceTimeSJF.push(processServiceTime);
                outMemSJF.push(processMemorySize);
                waitTimeSJF.push(totalTurnaroundSJF);
                long totalTime = totalTurnaroundSJF + processServiceTime;
                outTotalTimeSJF.push(totalTime);
                processes.pop();
                processorFull2SJF = true;//signal that a processor is now running a process
                if(temp.serviceTime !=0){
                    temp2SJF = processor2(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{//if the process is too large for the memeory size of the processor, it will push it to the appropiate queue for the processor that has enough size and remove it from the processes queue
                if(processMemorySize > 2 && processMemorySize < 5){
                    fourGBSJF.push(temp);
                    processes.pop();
                }
                else{
                    eightGBSJF.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull3SJF == false){//check if processor 3 is empty
            if(fourGBSJF.empty() == false){//if there are any processes that need to run on the 4GB memory processor then take it from that queue
                priorityNode temp = fourGBSJF.top();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory3){
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumberSJF.push(ID);
                    outputServiceTimeSJF.push(processServiceTime);
                    outMemSJF.push(processMemorySize);
                    waitTimeSJF.push(totalTurnaroundSJF);
                    long totalTime = totalTurnaroundSJF + processServiceTime;
                    outTotalTimeSJF.push(totalTime);
                    fourGBSJF.pop();
                    processorFull3SJF = true;//signal that a processor is now running a process
                    temp3SJF = processor3(0,processServiceTime, ID, processServiceTime);
                }
            }
            else{//if there aren't any processes waiting from in the 4GB queue then take one from the processes queue and put it on the processor
                priorityNode temp = processes.top();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory3){//if the memory of the process fits the memory of the processes put the process onto the processor and then remove the process from the queue
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumberSJF.push(ID);
                    outputServiceTimeSJF.push(processServiceTime);
                    outMemSJF.push(processMemorySize);
                    waitTimeSJF.push(totalTurnaroundSJF);
                    long totalTime = totalTurnaroundSJF + processServiceTime;
                    outTotalTimeSJF.push(totalTime);
                    processes.pop();
                    processorFull3SJF = true; //signal that a processor is now running a process
                    if(temp.serviceTime !=0){
                        temp3SJF = processor3(0,processServiceTime, ID, processServiceTime);
                    }
                }
                else{//if the memory of the process is too large for this processor, then put it on the 8GB queue and remove it from processe queue
                    eightGBSJF.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull4SJF == false){//check if processor4 is empty
            if(eightGBSJF.empty() == false){// if there are any processes in the 8GB queue, then remove that process from the queue and put it to run on the processor
                priorityNode temp = eightGBSJF.top();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory4){
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumberSJF.push(ID);
                    outputServiceTimeSJF.push(processServiceTime);
                    outMemSJF.push(processMemorySize);
                    waitTimeSJF.push(totalTurnaroundSJF);
                    long totalTime = totalTurnaroundSJF + processServiceTime;
                    outTotalTimeSJF.push(totalTime);
                    eightGBSJF.pop();
                    processorFull4SJF = true; //signal that a processor is now running a process
                    temp4SJF = processor4(0,processServiceTime, ID, processServiceTime);
                }
            }
            else{//if there are no processes in the 8GB queue, take a process from the processor queue and put it on the CPU to execute
                priorityNode temp = processes.top();
                int processMemorySize = temp.memorySize;
                if(processMemorySize <= memory4){
                    long processServiceTime = temp.serviceTime;
                    int ID = temp.processID;
                    IDNumberSJF.push(ID);
                    outputServiceTimeSJF.push(processServiceTime);
                    outMemSJF.push(processMemorySize);
                    waitTimeSJF.push(totalTurnaroundSJF);
                    long totalTime = totalTurnaroundSJF + processServiceTime;
                    outTotalTimeSJF.push(totalTime);
                    processes.pop();
                    processorFull4SJF = true; //signal that a processor is now running a process
                    if(temp.serviceTime != 0){
                        temp4SJF = processor4(0, processServiceTime, ID, processServiceTime);
                    }
                }
            }
        }
    }

    //Once the queues are empty, the while loop above will continue running. However, there still could be processes that haven't finished running. 
    //This ensures that the processes remaining on the processors will run until completion
    while(temp1SJF.remainingServiceTime > 0 || temp2SJF.remainingServiceTime > 0 || temp3SJF.remainingServiceTime > 0 || temp4SJF.remainingServiceTime > 0){//while that are still processes with service time
        if(temp1SJF.remainingServiceTime > 0){//if process on processor1 has service time left, run
            temp1SJF = processor1(speed1, temp1SJF.remainingServiceTime, temp1SJF.processID, temp1SJF.serviceTime);
        }
        else if(finish1SJF == false){//flag as finished running, in order to handle total turnaround time calculation
            totalTurnaroundSJF = totalTurnaroundSJF + temp1SJF.serviceTime;
            temp2SJF.serviceTime = temp2SJF.serviceTime - temp1SJF.serviceTime;
            temp3SJF.serviceTime = temp3SJF.serviceTime - temp1SJF.serviceTime;
            temp4SJF.serviceTime = temp4SJF.serviceTime - temp1SJF.serviceTime;
            finish1SJF = true;
        }
        if(temp2SJF.remainingServiceTime > 0){//if process on processor2 has service time left, run
            temp2SJF = processor2(speed2, temp2SJF.remainingServiceTime, temp2SJF.processID, temp2SJF.serviceTime);
        }
        else if(finish2SJF == false){//flag as finished running, in order to handle total turnaround time calculation
            totalTurnaroundSJF = totalTurnaroundSJF + temp2SJF.serviceTime;
            temp1SJF.serviceTime = temp1SJF.serviceTime - temp2SJF.serviceTime;
            temp3SJF.serviceTime = temp3SJF.serviceTime - temp2SJF.serviceTime;
            temp4SJF.serviceTime = temp4SJF.serviceTime - temp2SJF.serviceTime;   
            finish2SJF = true;
        }     
        if(temp3SJF.remainingServiceTime > 0){//if process on processor3 has service time left, run
            temp3SJF = processor3(speed3, temp3SJF.remainingServiceTime, temp3SJF.processID, temp3SJF.serviceTime);
        }
        else if(finish3SJF == false){//flag as finished running, in order to handle total turnaround time calculation
            totalTurnaroundSJF = totalTurnaroundSJF + temp3SJF.serviceTime;
            temp1SJF.serviceTime = temp1SJF.serviceTime - temp3SJF.serviceTime;
            temp2SJF.serviceTime = temp2SJF.serviceTime - temp3SJF.serviceTime;
            temp4SJF.serviceTime = temp4SJF.serviceTime - temp3SJF.serviceTime;
            finish3SJF = true;
        }        
        if(temp4SJF.remainingServiceTime > 0){//if process on processor4 has service time left, run
            temp4SJF = processor4(speed4, temp4SJF.remainingServiceTime, temp4SJF.processID, temp4SJF.serviceTime);
        }
        else if(finish4SJF == false){//flag as finished running, in order to handle total turnaround time calculation
            totalTurnaroundSJF = totalTurnaroundSJF + temp4SJF.serviceTime;
            temp1SJF.serviceTime = temp1SJF.serviceTime - temp4SJF.serviceTime;
            temp2SJF.serviceTime = temp2SJF.serviceTime - temp4SJF.serviceTime;
            temp3SJF.serviceTime = temp3SJF.serviceTime - temp4SJF.serviceTime;
            finish4SJF = true;
        }        
    }
    
    //The code used to output all the data collected to a file called results.txt
    ofstream resultsSJF("results.txt");
    resultsSJF << "Scenario " << scenario << " \n";
    resultsSJF << "Total Turnaround time is " << totalTurnaroundSJF  << " cycles \n";
    int i = 0;
    long avgWaitTime = 0;
    long avgTurnTime = 0;
    long avgServTime = 0;
    double avgmemSize = 0;
    while(i < 40){
        resultsSJF << "\n";
        resultsSJF << "ID Number: " << IDNumberSJF.front() << "\n";
        resultsSJF << "Service Time: " << outputServiceTimeSJF.front() << " cycles\n";
        resultsSJF << "Memory Requirements: " << outMemSJF.front() << "GB \n";
        resultsSJF << "Wait Time: " << waitTimeSJF.front() << " cycles \n";
        resultsSJF << "Total Time: " << outTotalTimeSJF.front() << " cycles \n";
        avgWaitTime = avgWaitTime + waitTimeSJF.front();
        avgTurnTime = avgTurnTime + outTotalTimeSJF.front();
        avgServTime = avgServTime + outputServiceTimeSJF.front();
        avgmemSize = avgmemSize + outMemSJF.front();
        IDNumberSJF.pop();
        outputServiceTimeSJF.pop();
        outMemSJF.pop();
        waitTimeSJF.pop();
        outTotalTimeSJF.pop();
        i++;        
    }
    resultsSJF << "\n";
    avgWaitTime = avgWaitTime/40;
    resultsSJF << "Average wait time is: " << avgWaitTime << " cycles \n";
    avgTurnTime = avgTurnTime/40;
    resultsSJF << "Average turnaround time is: " << avgTurnTime << " cycles\n";
    avgServTime = avgServTime/40;
    resultsSJF << "Average service time is: " << avgServTime << " cycles\n";
    avgmemSize = avgmemSize/40;
    resultsSJF << "Average memory size is: " << avgmemSize << "GB";
    resultsSJF.close();
}