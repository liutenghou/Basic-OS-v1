/* ctsw.c : context switcher
 */

#include <xeroskernel.h>

/* Your code goes here - You will need to write some assembly code. You must
   use the gnu conventions for specifying the instructions. (i.e this is the
   format used in class and on the slides.) You are not allowed to change the
   compiler/assembler options or issue directives to permit usage of Intel's
   assembly language conventions.
*/

//contextswitch() takes pointer to current process,
// switches to context of that process and lets it run via iret
// IDT has entrypoint for this function
void _ISREntryPoint();
static void *k_stack;
static unsigned int ESP;
static unsigned int EAX;
static void (*func)(void);


//saves kernel state
//loads user process state into registers
//iret executes user process code

//saves user process state
//loads kernel state back to registers
//returns to dispatcher to handle syscall
int contextswitch(struct pcb* p){

	ESP = (unsigned int)p->esp;
	__asm __volatile("\
			pushf \n\
			pusha \n\
			movl %%esp, k_stack \n\
			movl ESP, %%esp \n\
			popa \n\
			iret \n\
	_ISREntryPoint: \n\
		pusha \n\
		movl %%esp, ESP \n\
		movl k_stack, %%esp \n\
		movl %%eax, EAX \n\
		movl %%edx, func \n\
		popa \n\
		popf \n\
		"
		:
		:
		: "%eax"
		);
	p->function = (void (*)(void))func;
	p->esp = (unsigned long*)ESP;
	//kprintf("<ctsw: eax:%d, func:%d >", EAX, p->function);
	return EAX;
}


//contextinit() initializes the context switcher and sets the entrypoint for contextswitch in the IDT
void contextinit(void){
	set_evec(CSENTRY, (int)_ISREntryPoint);
}
