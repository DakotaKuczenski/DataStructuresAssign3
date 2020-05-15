#include <stdlib.h>

#include "multilevelQueueScheduler.h"

void attemptPromote( schedule *ps );
static int timer = -1;

/* initializeSchedule
 * input: none
 * output: a schedule
 *
 * Initialize and return a schedule struct.
 */
schedule* initializeSchedule( ) {
    schedule *ps = malloc( sizeof(schedule) );
    
    ps -> frontqueue = createQueue();
    ps -> backqueue = createQueue();
    
    /* TODO: initialize data in schedule  DONE */
    return ps;
}

/* unfinishedSchedule
 * input: a schedule
 * output: bool (true or false)
 *
 * Check if there are any processes still in the queues.
 * Return TRUE if there is.  Otherwise false.
 */

bool unfinishedSchedule( schedule *ps ) {
    
    if (isEmpty(ps -> frontqueue) && isEmpty(ps -> backqueue))
    {
        return false;
    }
    /* TODO: check if there are any process still in a queue.  Return TRUE if there is. DONE */
    return true;
}

/* scheduleProcess
 * input: a schedule, a string, an int, a priority
 * output: void
 *
 * Create a new process with the provided name, runtime, and priority.
 * Add that process to the appropriate queue
 */
void scheduleProcess( schedule *ps, char *functionName, int runtime, priority p ) {
    
    processData *intdataoutput;
    intdataoutput = initializeProcessData(functionName);
    
    queueType processdefined = malloc(sizeof(process));
    
    processdefined -> fName = functionName;
    processdefined->process = intdataoutput;
    processdefined -> cyclesleft = runtime;
    processdefined->cycles = runtime;
    processdefined -> cycleshappened = 0;
    
    if (p == BACKGROUND)
    {
        enqueue(ps -> backqueue, processdefined);
        processdefined -> starrtTime = timer;
    }
    if(p == FOREGROUND)
    {
        enqueue(ps -> frontqueue, processdefined);
    }
    else
    {
        return;
    }
    
    /* TODO: complete this function.
     The function "initializeProcessData" in processSimulator.c will be useful in completing this. DONE */
}

/* simulateTimeStep
 * input: a schedule
 * output: a string
 *
 * Use the schedule to determine the next process to run.
 * If process being run starts a new process it will return a string.
 * This function should just return this string.
 */


char* simulateTimeStep( schedule *ps ) {
    /* TODO: complete this function.
     The functions "runProcess", "freeProcessData", and "promoteProcess" in processSimulator.c will be useful in completing this. */
    
    char *name = NULL;
    
    
    if (!isEmpty(ps -> backqueue) && (timer - (getNext(ps -> backqueue) -> starrtTime) >= 50))
    {
        process* promotion = dequeue(ps -> backqueue);
        promoteProcess(promotion -> fName, promotion -> process);
        enqueue(ps -> frontqueue, promotion);
    }
    if (!isEmpty(ps -> frontqueue))
    {
        
        queueType returning;
        returning = getNext(ps -> frontqueue);
        if ((returning -> cyclesleft -- ) != 0 ){
            timer++;
            name = runProcess(returning -> fName, returning -> process);
            
            returning -> cycleshappened ++;
            
            if (returning -> cyclesleft != 0 && returning -> cycles - returning -> cyclesleft == 5)
            {
                returning -> cycles = returning -> cyclesleft;
                returning = dequeue(ps -> frontqueue);
                enqueue (ps -> frontqueue, returning);
            }
        } else {
            returning = dequeue(ps -> frontqueue);
            freeProcessData(returning -> process);
            free(returning -> fName);
            free(returning);
            free(name);
        }
        return name;
    }
    else if (!isEmpty(ps -> backqueue))
    {
        queueType returning;
        returning = getNext(ps -> backqueue);
        if ((returning -> cyclesleft -- ) != 0 ){
            timer++;
            name = runProcess(returning -> fName, returning -> process);
            returning -> cycleshappened ++;
            
        }else {
            returning = dequeue(ps -> backqueue);
            freeProcessData(returning -> process);
            free(returning -> fName);
            free(returning);
            free(name);
        }
        return name;
    }
    
    
    
    
    /* TODO: check if there are any process still in a queue.  Return TRUE if there is. DONE */
    return NULL;
}

/* freeSchedule
 * input: a schedule
 * output: none
 *
 * Free all of the memory associated with the schedule.
 */
void freeSchedule( schedule *ps ) {
    /* TODO: free any data associated with the schedule. */
    free(ps -> frontqueue);
    free(ps -> backqueue);
    free(ps);
}
