/* syscall.c : syscalls
 */

#include <xeroskernel.h>

/* Your code goes here */

static int result;
static int callLocal;

//call: CREATE, YIELD, STOP
//returns: pid of process
int syscall(int call, unsigned int numargs, char *sargs){
	callLocal = call;
		kprintf(" call: %d ", call);
		//TODO: put arguments in register
		//asm volatile ("movl %0, %esp" : "g" (userstack));
		__asm __volatile("\
				movl %eax, callLocal\n\
				int $49\n\
				movl result, %eax\n\
			"
			);
		kprintf(" result: %d ", result);
		return result;
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
