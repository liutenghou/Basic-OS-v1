/* syscall.c : syscalls
 */

#include <xeroskernel.h>
/* Your code goes here */


//call: CREATE, YIELD, STOP
//returns: pid of process
int syscall(int call, unsigned int numargs, void *funcptr){
	int *function = NULL;
	if(numargs == 1){
		function = (void (*)(void))funcptr;
	}
	int result;
		kprintf(" 0call: %d ", call);
		//TODO: put arguments in register
		//asm volatile ("movl %0, %esp" : "g" (userstack));
		__asm __volatile("movl %1, %%eax;"
						"movl %2, %%edx;"
						"int $49;"
						"movl %%eax, %0;"
			: "=r" (result)					/*output operand*/
			: "r" (call), "r" (function)	/*input operand*/
			: "%eax"						/*clobbered register*/
			);
		kprintf(" 1result: %d, function:%d *", result, function);
	return result;
}

unsigned int syscreate( void (*func)(void)){
	//note: stack size is always PROCSIZE
	kprintf(" syscreate:%d ", func);
	return syscall(CREATE, 1, (void*)func);
}

//yield to next ready process
void sysyield( void ){
	syscall(YIELD, 0, (void*)0);
}

//stop and cleanup
void sysstop( void ){
	syscall(STOP, 0, (void*)0);
}
