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

int contextswitch(struct pcb* p){
	kprintf("\nc:");

	ESP = p->esp;
	kprintf("ESP:%d *", ESP);
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
		popa \n\
		popf \n\
		"
		:
		:
		: "%eax"
		);
	p->esp = ESP;
	kprintf(" END CS\n");
	return YIELD;
}


//contextinit() initializes the context switcher and sets the entrypoint for contextswitch in the IDT
void contextinit(void){
	kprintf(" INITCONTEXT ");
	set_evec(49, _ISREntryPoint);
}
