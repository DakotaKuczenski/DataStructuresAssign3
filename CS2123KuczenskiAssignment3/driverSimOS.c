#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "queue.h"
#include "multilevelQueueScheduler.h"
#include "processSimulator.h"

void testFile( const char dataFile[], char *(*f)( char *));

int getRuntime(char* processName);
priority getPriority(char* processName);

int main( int argc, char *argv[] )
{
    int i = 0;
    char *testData[] = {"B|LNG|00|10|7|03|00","F|SMP|00|30|08|31|00","F|RPD|00|09|03|32|00","F|VID|00|40|99|01|00"};

    schedule *ps = initializeSchedule();
    char *name;

    //Schedule testData
    for( i=0; i<4; i++){
        name = (char *)malloc(strlen(testData[i])+1);
        if( name==NULL ){
            fprintf(stderr, "main: Allocation of memory failed.");
            exit(-1);
        }
        strcpy( name, testData[i] );
        scheduleProcess( ps, name, getRuntime(name), getPriority(name) );
    }

    //Simulate time steps until no process is still running
    while( unfinishedSchedule( ps ) ){
        name = simulateTimeStep( ps );
        if( name!= NULL )
            scheduleProcess( ps, name, getRuntime(name), getPriority(name) );
    }
    freeSchedule( ps );

    return 0;
}

int getRuntime(char* processName){
    char runtimeString[3];
    int runtime;
    int p = abs((int)getPriority(processName)-1);
    //Read runtime from the 4th |-separated value in the string
    sscanf(processName, "%*[^|]|%*[^|]|%*[^|]|%[^|]", runtimeString);
    sscanf(runtimeString, "%d", &runtime);

    return max(runtime/powInt(2,p),1);
}

priority getPriority(char* processName){
    return processName[0]=='B';
}
