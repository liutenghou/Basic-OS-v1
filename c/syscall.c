/* syscall.c : syscalls
 */

#include <xeroskernel.h>

/* Your code goes here */


int syscall(int num, char* inst, ...){
	int result = 1;

	//TODO: put arguments in register
	__asm __volatile("\
			movl %%eax, inst\n\
			int 49\n\
			movl __result, %%eax\n\
		"
		:
		:
		: "%eax"
		);

	return result;
}


extern unsigned int syscreate( void (*func)(void), int stack ){
	return syscall(3, "CREATE", *func, stack);
}


extern void sysyield( void ){
	syscall(1, "YEILD");
}
extern void sysstop( void ){
	syscall(1, "STOP");
}
