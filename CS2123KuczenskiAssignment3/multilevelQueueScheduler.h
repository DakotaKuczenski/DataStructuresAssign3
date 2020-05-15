#ifndef _multilevelQueueScheduler_h
#define _multilevelQueueScheduler_h
#include <stdlib.h>
#include <stdbool.h>

#include "process.h"
#include "queue.h"
#include "processSimulator.h"

typedef enum priority { FOREGROUND, BACKGROUND } priority;

/* struct schedule (only accessed in student written code)
 *
 * Data related to the order the processes should be scheduled in.
 * At minimum it should store the FOREGROUND and BACKGROUND queues.
 */
typedef struct schedule
{
    Queue* frontqueue;
    
    Queue* backqueue;
    
    //TODO: Put the data for your schedule program here! DONE
}  schedule;

schedule* initializeSchedule( );
bool unfinishedSchedule( schedule *ps );
void scheduleProcess( schedule *ps, char *functionName, int runtime, priority p );
char* simulateTimeStep( schedule *ps );
void freeSchedule( schedule *ps );

#endif
