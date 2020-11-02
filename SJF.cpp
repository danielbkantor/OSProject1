//Daniel Kantor & Derek Levine
#include "SJF.h"
#include "processor1.h"
#include "processor2.h"
#include "processor3.h"
#include "processor4.h"
#include "struct.h"
#include <fstream>

bool processorFull1SJF = false;
bool processorFull2SJF = false;
bool processorFull3SJF = false;
bool processorFull4SJF = false;
bool finish1SJF = false;
bool finish2SJF = false;
bool finish3SJF = false;
bool finish4SJF = false;
data temp1SJF(0,0,0,0);
data temp2SJF(0,0,0,0);
data temp3SJF(0,0,0,0);
data temp4SJF(0,0,0,0);
priority_queue<priorityNode> fourGBSJF;
priority_queue<priorityNode> eightGBSJF;
queue<int> IDNumberSJF;
queue<long> outputServiceTimeSJF;
queue<int> outMemSJF;
queue<long> waitTimeSJF;
queue<long> outTotalTimeSJF;
long totalTurnaroundSJF = 0;
 
void SJF(priority_queue<priorityNode> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4, int scenario){
    while(!processes.empty() || !fourGBSJF.empty() || !eightGBSJF.empty()){
        if(processorFull1SJF == true && processorFull2SJF == true && processorFull3SJF == true && processorFull4SJF == true){
            if(temp1SJF.remainingServiceTime > 0){
                temp1SJF = processor1(speed1, temp1SJF.remainingServiceTime, temp1SJF.processID, temp1SJF.serviceTime);
            }
            else{
                totalTurnaroundSJF = totalTurnaroundSJF + temp1SJF.serviceTime;
                temp2SJF.serviceTime = temp2SJF.serviceTime - temp1SJF.serviceTime;
                temp3SJF.serviceTime = temp3SJF.serviceTime - temp1SJF.serviceTime;
                temp4SJF.serviceTime = temp4SJF.serviceTime - temp1SJF.serviceTime;
                processorFull1SJF = false;
                continue;
            }
            if(temp2SJF.remainingServiceTime > 0){
                temp2SJF = processor2(speed2, temp2SJF.remainingServiceTime, temp2SJF.processID, temp2SJF.serviceTime);
            }  
            else{
                totalTurnaroundSJF = totalTurnaroundSJF + temp2SJF.serviceTime;
                temp1SJF.serviceTime = temp1SJF.serviceTime - temp2SJF.serviceTime;
                temp3SJF.serviceTime = temp3SJF.serviceTime - temp2SJF.serviceTime;
                temp4SJF.serviceTime = temp4SJF.serviceTime - temp2SJF.serviceTime;
                processorFull2SJF = false;
                continue;
            }
            if(temp3SJF.remainingServiceTime > 0){
                temp3SJF = processor3(speed3, temp3SJF.remainingServiceTime, temp3SJF.processID, temp3SJF.serviceTime);
            }
            else{
                totalTurnaroundSJF = totalTurnaroundSJF + temp3SJF.serviceTime;
                temp1SJF.serviceTime = temp1SJF.serviceTime - temp3SJF.serviceTime;
                temp2SJF.serviceTime = temp2SJF.serviceTime - temp3SJF.serviceTime;
                temp4SJF.serviceTime = temp4SJF.serviceTime - temp3SJF.serviceTime;
                processorFull3SJF = false;
                continue;
            }
            if(temp4SJF.remainingServiceTime > 0){
                temp4SJF = processor4(speed4, temp4SJF.remainingServiceTime, temp4SJF.processID, temp4SJF.serviceTime);
            }   
            else{
                totalTurnaroundSJF = totalTurnaroundSJF + temp4SJF.serviceTime;
                temp1SJF.serviceTime = temp1SJF.serviceTime - temp4SJF.serviceTime;
                temp2SJF.serviceTime = temp2SJF.serviceTime - temp4SJF.serviceTime;
                temp3SJF.serviceTime = temp3SJF.serviceTime - temp4SJF.serviceTime;
                processorFull4SJF = false;
                continue;
            }
        }
        else if(processorFull1SJF == false){
            priorityNode temp = processes.top();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory1){
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                IDNumberSJF.push(ID);
                outputServiceTimeSJF.push(processServiceTime);
                outMemSJF.push(processMemorySize);
                waitTimeSJF.push(totalTurnaroundSJF);
                long totalTime = totalTurnaroundSJF + processServiceTime;
                outTotalTimeSJF.push(totalTime);
                processes.pop();
                processorFull1SJF = true;
                if(temp.serviceTime !=0){
                   temp1SJF = processor1(0, processServiceTime, ID, processServiceTime); 
                }
            }
            else{
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
        else if(processorFull2SJF == false){
            priorityNode temp = processes.top();
            int processMemorySize = temp.memorySize;
            if(processMemorySize <= memory2){
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                IDNumberSJF.push(ID);
                outputServiceTimeSJF.push(processServiceTime);
                outMemSJF.push(processMemorySize);
                waitTimeSJF.push(totalTurnaroundSJF);
                long totalTime = totalTurnaroundSJF + processServiceTime;
                outTotalTimeSJF.push(totalTime);
                processes.pop();
                processorFull2SJF = true;
                if(temp.serviceTime !=0){
                    temp2SJF = processor2(0, processServiceTime, ID, processServiceTime);
                }
            }
            else{
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
        else if(processorFull3SJF == false){
            if(fourGBSJF.empty() == false){
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
                    processorFull3SJF = true;
                    temp3SJF = processor3(0,processServiceTime, ID, processServiceTime);
                }
            }
            else{
                priorityNode temp = processes.top();
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
                    processes.pop();
                    processorFull3SJF = true;
                    if(temp.serviceTime !=0){
                        temp3SJF = processor3(0,processServiceTime, ID, processServiceTime);
                    }
                }
                else{
                    eightGBSJF.push(temp);
                    processes.pop();
                }
            }
        }
        else if(processorFull4SJF == false){
            if(eightGBSJF.empty() == false){
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
                    processorFull4SJF = true;
                    temp4SJF = processor4(0,processServiceTime, ID, processServiceTime);
                }
            }
            else{
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
                    processorFull4SJF = true;
                    if(temp.serviceTime != 0){
                        temp4SJF = processor4(0, processServiceTime, ID, processServiceTime);
                    }
                }
            }
        }
    }
    while(temp1SJF.remainingServiceTime > 0 || temp2SJF.remainingServiceTime > 0 || temp3SJF.remainingServiceTime > 0 || temp4SJF.remainingServiceTime > 0){
        if(temp1SJF.remainingServiceTime > 0){
            temp1SJF = processor1(speed1, temp1SJF.remainingServiceTime, temp1SJF.processID, temp1SJF.serviceTime);
        }
        else if(finish1SJF == false){
            totalTurnaroundSJF = totalTurnaroundSJF + temp1SJF.serviceTime;
            temp2SJF.serviceTime = temp2SJF.serviceTime - temp1SJF.serviceTime;
            temp3SJF.serviceTime = temp3SJF.serviceTime - temp1SJF.serviceTime;
            temp4SJF.serviceTime = temp4SJF.serviceTime - temp1SJF.serviceTime;
            finish1SJF = true;
        }
        if(temp2SJF.remainingServiceTime > 0){
            temp2SJF = processor2(speed2, temp2SJF.remainingServiceTime, temp2SJF.processID, temp2SJF.serviceTime);
        }
        else if(finish2SJF == false){
            totalTurnaroundSJF = totalTurnaroundSJF + temp2SJF.serviceTime;
            temp1SJF.serviceTime = temp1SJF.serviceTime - temp2SJF.serviceTime;
            temp3SJF.serviceTime = temp3SJF.serviceTime - temp2SJF.serviceTime;
            temp4SJF.serviceTime = temp4SJF.serviceTime - temp2SJF.serviceTime;   
            finish2SJF = true;
        }     
        if(temp3SJF.remainingServiceTime > 0){
            temp3SJF = processor3(speed3, temp3SJF.remainingServiceTime, temp3SJF.processID, temp3SJF.serviceTime);
        }
        else if(finish3SJF == false){
            totalTurnaroundSJF = totalTurnaroundSJF + temp3SJF.serviceTime;
            temp1SJF.serviceTime = temp1SJF.serviceTime - temp3SJF.serviceTime;
            temp2SJF.serviceTime = temp2SJF.serviceTime - temp3SJF.serviceTime;
            temp4SJF.serviceTime = temp4SJF.serviceTime - temp3SJF.serviceTime;
            finish3SJF = true;
        }        
        if(temp4SJF.remainingServiceTime > 0){
            temp4SJF = processor4(speed4, temp4SJF.remainingServiceTime, temp4SJF.processID, temp4SJF.serviceTime);
        }
        else if(finish4SJF == false){
            totalTurnaroundSJF = totalTurnaroundSJF + temp4SJF.serviceTime;
            temp1SJF.serviceTime = temp1SJF.serviceTime - temp4SJF.serviceTime;
            temp2SJF.serviceTime = temp2SJF.serviceTime - temp4SJF.serviceTime;
            temp3SJF.serviceTime = temp4SJF.serviceTime - temp4SJF.serviceTime;
            finish4SJF = true;
        }        
    }
  
    ofstream resultsSJF("SJF.txt");
    resultsSJF << "Scenario " << scenario << " \n";
    resultsSJF << "Total Turnaround time is " << totalTurnaroundSJF  << " cycles \n";
    int i = 0;
    long avgWaitTime = 0;
    long avgTurnTime = 0;
    while(i < 40){
        resultsSJF << "\n";
        resultsSJF << "ID Number: " << IDNumberSJF.front() << "\n";
        resultsSJF << "Service Time: " << outputServiceTimeSJF.front() << " cycles\n";
        resultsSJF << "Memory Requirements: " << outMemSJF.front() << "GB \n";
        resultsSJF << "Wait Time: " << waitTimeSJF.front() << " cycles \n";
        resultsSJF << "Total Time: " << outTotalTimeSJF.front() << " cycles \n";
        avgWaitTime = avgWaitTime + waitTimeSJF.front();
        avgTurnTime = avgTurnTime + outTotalTimeSJF.front();
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
    resultsSJF << "Average turnaround time is: " << avgTurnTime << " cycles";
    resultsSJF.close();
}