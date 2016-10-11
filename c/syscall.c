/* syscall.c : syscalls
 */

#include <xeroskernel.h>

/* Your code goes here */
//call: CREATE, YIELD, STOP
//returns: pid of process
int syscall(int call, char *sargs){

	return 0;
}

unsigned int syscreate( void (*func)(void), int stack ){

	return 0;
}

//yield to next ready process
void sysyield( void ){

}

//stop and cleanup
void sysstop( void ){

}
