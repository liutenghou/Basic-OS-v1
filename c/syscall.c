/* syscall.c : syscalls
 */

#include <xeroskernel.h>

/* Your code goes here */
//call: CREATE, YIELD, STOP
//returns: pid of process
int syscall(int call, unsigned int numargs, char *sargs){

	return 0;
}

unsigned int syscreate( void (*func)(void)){
	//note: stack size is always PROCSIZE
	syscall(CREATE, 1, func);
	return 0;
}

//yield to next ready process
void sysyield( void ){
	syscall(YIELD, 0, NULL);
}

//stop and cleanup
void sysstop( void ){
	syscall(STOP, 0, NULL);
}
