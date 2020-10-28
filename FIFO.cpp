#include "FIFO.h"
#include "processor1.h"
#include "processor2.h"
#include "processor3.h"
#include "processor4.h"

bool processorFull1 = false;
bool processorFull2 = false;
bool processorFull3 = false;
bool processorFull4 = false;
bool openProcessor = true;


/*void FIFO(queue<node> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4){
    while(!processes.empty()){
        if(openProcessor == true){
            node temp = processes.front();
            long processServiceTime = temp.serviceTime;
            int processMemorySize = temp.memorySize;
            processes.pop();

            if(processorFull1 == false){
                if(processMemorySize <= memory1){
                    processorFull1 = true;
                    processor1(speed1, processServiceTime);
                    processorFull1 = false;

                }
            }
            else if(processorFull2 == false){
                if(processMemorySize <= memory2){
                    processorFull2 = true;
                    processor2(speed2, processServiceTime);
                    processorFull2 = false;

                } 
            }
            else if(processorFull3 == false){
                if(processMemorySize <= memory3){
                    processorFull3 = true;
                    processor3(speed3, processServiceTime);
                    processorFull3 = false;

                }
            }
            else if(processorFull4 == false){
                if(processMemorySize >= memory4){
                    processorFull4 = true;
                    processor4(speed4, processServiceTime);
                    processorFull4 = false;
                }
            }
            else{

            }
        }
    }
}
*/

void FIFO(queue<node> processes, long speed1, long speed2, long speed3, long speed4, int memory1, int memory2, int memory3, int memory4){
    int pid1, pid2, pid3, pid4;

    while(!processes.empty()){
        if(processorFull1 == true && processorFull2 == true && processorFull3 == true && processorFull4 == true){
            openProcessor = false;
        }
        else{
            openProcessor = true;
        }
        if(openProcessor == true){
            node temp = processes.front();
            long processServiceTime = temp.serviceTime;
            int processMemorySize = temp.memorySize;
            processes.pop();
            pid1 = fork();
            if(pid1 == 0){
                if(processorFull1 == false){
                    if(processMemorySize <= memory1){
                        processorFull1 = true;
                        processor1(speed1, processServiceTime);
                        processorFull1 = false;
                    }
                }
            }
            else{
                pid2 = fork();
                if(pid2 == 0){
                    if(processorFull2 == false){
                         if(processMemorySize <= memory2){
                             processorFull2 = true;
                             processor2(speed2, processServiceTime);
                             processorFull2 = false;

                         } 
                    }
                }
                else{
                    pid3 = fork();
                    if(pid3 == 0){
                        if(processorFull3 == false){
                            if(processMemorySize <= memory3){
                              processorFull3 = true;
                              processor3(speed3, processServiceTime);
                              processorFull3 = false;

                            }   
                        }       
                    }   
                    else{
                        if(processorFull4 == false){
                            if(processMemorySize >= memory4){
                                processorFull4 = true;
                                processor4(speed4, processServiceTime);
                                processorFull4 = false;
                            }
                        }
                    }
                }
            }
        }
    }
}
