#include <iostream>
#include "Sorting.h"
using namespace std;


int main(){
    initializeCounters();
    for(int i=1;i<=3;i++){
        resetCounters();
        runSimulation(i,100);
        printCounters(i,100);
    }

    for(int i=1;i<=3;i++){
        resetCounters();
        runSimulation(i,1000);
        printCounters(i,1000);
    }

    return 0;
}


