#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN_PID 300
#define MAX_PID 5000
#define CB CHAR_BIT

int sz = MAX_PID - MIN_PID + 1;

unsigned char *unsignedChar;

int allocate_map();
int allocate_pid();
void release_pid(int pid);

int main() 
{
    int map = allocate_map();
    if (map == 1) {
        printf("\nBitmap Data Structure initialized.\n");
        int id = 0, i = 0;

    //create 20 processes
        while (i < 20) {
            int val = allocate_pid();
            printf("\nProcess %d: pid = %d", i+1, val);
            i++;
        }
    //release a few processes
    release_pid(303); printf("\nProcess 303 released.");
    release_pid(308); printf("\nProcess 308 released.");
    release_pid(309); printf("\nProcess 309 released.");

    //allocate a few more processes after this release
        int val = allocate_pid(); printf("\nProcess %d : pid = %d", ++i, val); //should be 303
    val = allocate_pid(); printf("\nProcess %d : pid = %d\n", ++i, val); //should be 308
    }
    else printf("\nFailed to initialize data structure.\n");
}

/* Creates and initializes a bitmap data structure for representing pids;
 returns —1 for unsuccessful, 1 for successful */
int allocate_map() {
    unsignedChar = (unsigned char*)malloc((sz+CB-1)/CB * sizeof(char));
    if (unsignedChar) return 1;
    return -1;
}

/* Allocates and returns a pid; returns -1
if it is unable to allocate a pid (all pids are in use) */
int allocate_pid() {
    int i = 0;
    int pid = unsignedChar[i/CB] & (1 << (i & (CB-1)));
    while (pid != 0) {
        i++;
        pid = unsignedChar[i/CB] & (1 << (i & (CB-1)));
        }

    if (i+MIN_PID > MAX_PID) return -1;
    unsignedChar[i/CB] |= 1 << (i & (CB-1));
    return i+MIN_PID;
}

/* Releases a pid given a pid parameter*/
void release_pid(int pid) {
    if (pid < 300) {
        printf("\nInvalid PID: It should lie between 300 and 3000.");
        return;
    }
    int i = pid - MIN_PID;
    unsignedChar[i/CB] &= ~(1 << (i & (CB-1)));
}
