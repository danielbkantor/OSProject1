//Daniel Kantor & Derek Levine
#include <iostream>
#include <random>
#include <queue>
using namespace std;


struct node{
    long serviceTime;
    int memeorySize;
};

 int main(){

    queue <node> q;
    mt19937_64 seed(0); //Seed value for generation

    //Generate Service Times & Memory Requirements
    uniform_int_distribution<long> values1(10000000,10000000000000);
    uniform_int_distribution<int> values2(1,8);
    for (int i = 0; i < 40; i++) {
        long serviceTime = values1(seed);
        int memorySize = values2(seed);
        q.push(node{serviceTime, memorySize});
    }

    
   

}

