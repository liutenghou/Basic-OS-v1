/* syscall.c : syscalls
 */

#include <xeroskernel.h>
#include <stdarg.h>
/* Your code goes here */


//call: CREATE, YIELD, STOP
//returns: pid of process
int syscall(int call, unsigned int numargs, ...){
	va_list arguments;
	va_start(arguments, numargs);



	int result;
		kprintf(" call: %d ", call);
		//TODO: put arguments in register
		//asm volatile ("movl %0, %esp" : "g" (userstack));
		__asm __volatile("movl %1, %%eax;"
						"int $49;"
						"movl %%eax, %0;"
			: "=r" (result)		/*output operand*/
			: "r" (call)	/*input operand*/
			: "%eax"			/*clobbered register*/
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
