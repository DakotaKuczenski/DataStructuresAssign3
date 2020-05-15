#ifndef _process_h
#define _process_h

typedef struct processData
{
    char name[21];
    char TLN[4];
    int heap[30];
}  processData;

/* struct process (only accessed in student written code)
 *
 * The data associated with a specific process.
 * At minimum you need to track the process name,
 * and the number of cycles process still needs to run.
 */
typedef struct process
{
    char* fName;
    int cyclesleft;
    int cycleshappened;
    processData* process;
    int starrtTime;
    int cycles;
    
    //TODO: Put the data for your process here!
}  process;

#endif
