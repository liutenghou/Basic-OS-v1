/* syscall.c : syscalls
 */

#include <xeroskernel.h>

/* Your code goes here */


int syscall(int call, ...){
	int* result;
	int* cat = *call;

	//TODO: put arguments in register
	//asm volatile ("movl %0, %esp" : "g" (userstack));
	__asm __volatile("\
			movl %%eax, (cat)\n\
			int $49\n\
			movl (result), %%eax\n\
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
