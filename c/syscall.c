/* syscall.c : syscalls
 */

#include <xeroskernel.h>

/* Your code goes here */


int syscall(void* call, ...){
	int result = 1;

	//TODO: put arguments in register
	__asm __volatile("\
			movl %%eax, call\n\
			int 49\n\
			movl result, %%eax\n\
		"
		:
		:
		: "%eax"
		);

	return result;
}


extern unsigned int syscreate( void (*func)(void), int stack ){
	return syscall(100, *func, stack);
}


extern void sysyield( void ){
	syscall(101);
}
extern void sysstop( void ){
	syscall(0);
}
