//Daniel Kantor & Derek Levine
#include <iostream>
#include <random>
#include <queue>
#include "FIFO.h"
#include "SJF.h"
#include "struct.h"

int main(){

    int scenario; // Prompt the user to choose a scenario
    cout << "Which scenario do you want to run?\n";
    cout << "Enter 1 for Scenario 1 \n";
    cout << "Enter 2 for Scenario 2 \n";
    cout << "Enter 3 for Scenario 3 \n";
    cout << "Enter 4 for Scenario 4 \n";
    cin >> scenario;
    while(scenario < 1|| scenario >4){ // If the value the user chooses isn't an option, try again
        cout << "Wrong input, try again \n";
        cout << "Enter 1 for Scenario 1 \n";
        cout << "Enter 2 for Scenario 2 \n";
        cout << "Enter 3 for Scenario 3 \n";
        cout << "Enter 4 for Scenario 4 \n";
        cin >> scenario;
     }
    
    int algorithm; // Promppt the user to choose the scheduling algorithm they wish to use with their chosen scenario
    cout << "Which algorithm do you want to use? \n";
    cout << "Enter 1 for FIFO \n";
    cout << "Enter 2 for SJF \n";
    cin >> algorithm;
    while(algorithm < 1 || algorithm > 2){// If the value the user chooses isn't an option, try again
        cout << "Wrong input, try again \n";
        cout << "Enter 1 for FIFO \n";
        cout << "Enter 2 for SJF \n";
        cin >> algorithm;
    }

    long seedValue;
    cout << "What seed value do you want to use? \n";
    cin >> seedValue;

    mt19937_64 seed(seedValue); //Gets the seed value used for random number generation
    //Sets the distributions of values to be randomly generated
    uniform_int_distribution<long> values1(1000000,1000000000000);
    uniform_int_distribution<int> values2(1,8);

    if(scenario == 1){ //All proccesses have a speed of 3Ghz and a memory of 8GB
        if(algorithm == 1){
            queue <node> q; //Queue to store each struct in
            for (int i = 0; i < 40; i++) {//Generates the random service times and memory sizes for each of the 40 processes and puts them in a struct which is then put in a queue.
                    long serviceTime = values1(seed);
                    int memorySize = values2(seed);
                    int processID = (i+1);
                    cout << serviceTime << "\n" << memorySize << "\n";
                    q.push(node(serviceTime, memorySize, processID));  
            }
            FIFO(q,3,3,3,3,8,8,8,8,1);
        }
        
        if(algorithm == 2){
            priority_queue<priorityNode> pq; //Priority queue to store each struct in
            for (int i = 0; i < 40; i++) {//Generates the random service times and memory sizes for each of the 40 processes and puts them in a struct which is then put in a min priority queue
                long serviceTime = values1(seed);
                int memorySize = values2(seed);
                int processID = (i+1);
                cout << serviceTime << "\n" << memorySize << "\n";
                pq.push(priorityNode(serviceTime, memorySize, processID));  
            }
            SJF(pq,3,3,3,3,8,8,8,8,1);
        }
    }

    if(scenario == 2){//All four have identical speeds of 3GHz but P1 and P2 have 3GB of memory while P3 has 4GB and P4 has 8GB
        if(algorithm == 1){
            queue <node> q; //Queue to store each struct in
            for (int i = 0; i < 40; i++) {//Generates the random service times and memory sizes for each of the 40 processes and puts them in a struct which is then put in a queue.
                    long serviceTime = values1(seed);
                    int memorySize = values2(seed);
                    int processID = (i+1);
                    cout << serviceTime << "\n" << memorySize << "\n";
                    q.push(node(serviceTime, memorySize, processID));  
            }
            FIFO(q,3,3,3,3,2,2,4,8,2);
        }

        if(algorithm == 2){
            priority_queue<priorityNode> pq;//Priority queue to store each struct in
            for (int i = 0; i < 40; i++) {//Generates the random service times and memory sizes for each of the 40 processes and puts them in a struct which is then put in a min priority queue
                long serviceTime = values1(seed);
                int memorySize = values2(seed);
                int processID = (i+1);
                cout << serviceTime << "\n" << memorySize << "\n";
                pq.push(priorityNode(serviceTime, memorySize, processID));  
            }
            SJF(pq,3,3,3,3,2,2,4,8,2);
        }
    }

    if(scenario == 3){// All four have identical memmory availitbility of 8GB but each process has varying speeds, P1 and P2 are 2GHz, P3 is 3GHz, and P4 is 4GHz
        if(algorithm == 1){
            queue <node> q; //Queue to store each struct in
            for (int i = 0; i < 40; i++) {//Generates the random service times and memory sizes for each of the 40 processes and puts them in a struct which is then put in a queue.
                    long serviceTime = values1(seed);
                    int memorySize = values2(seed);
                    int processID = (i+1);
                    cout << serviceTime << "\n" << memorySize << "\n";
                    q.push(node(serviceTime, memorySize, processID));  
            }
            FIFO(q,2,2,3,4,8,8,8,8,3);
        }

        if(algorithm == 2){
            priority_queue<priorityNode> pq;//Priority queue to store each struct in
            for (int i = 0; i < 40; i++) {//Generates the random service times and memory sizes for each of the 40 processes and puts them in a struct which is then put in a min priority queue
                long serviceTime = values1(seed);
                int memorySize = values2(seed);
                int processID = (i+1);
                cout << serviceTime << "\n" << memorySize << "\n";
                pq.push(priorityNode(serviceTime, memorySize, processID));  
            }
           SJF(pq,2,2,3,4,8,8,8,8,3);
        }
    }

    if(scenario == 4){//Only the element at the top of the queue can be inspected, no sorting allowed prior to processing
        if(algorithm == 1){
            queue <node> q; //Queue to store each struct in
            for (int i = 0; i < 40; i++) {//Generates the random service times and memory sizes for each of the 40 processes and puts them in a struct which is then put in a queue.
                    long serviceTime = values1(seed);
                    int memorySize = values2(seed);
                    int processID = (i+1);
                    cout << serviceTime << "\n" << memorySize << "\n";
                    q.push(node(serviceTime, memorySize, processID));  
            }
            FIFO(q,3,3,3,3,8,8,8,8,4);
        }
        
        if(algorithm == 2){
            priority_queue<priorityNode> pq;//Priority queue to store each struct in
            for (int i = 0; i < 40; i++) {//Generates the random service times and memory sizes for each of the 40 processes and puts them in a struct which is then put in a min priority queue
                long serviceTime = values1(seed);
                int memorySize = values2(seed);
                int processID = (i+1);
                cout << serviceTime << "\n" << memorySize << "\n";
                pq.push(priorityNode(serviceTime, memorySize, processID));  
            }
            SJF(pq,3,3,3,3,8,8,8,8,4);
        }
    }
}

