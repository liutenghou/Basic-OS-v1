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
int contextswitch(struct pcb* p){
	return 100;
}


//contextinit() initializes the context switcher and sets the entrypoint for contextswitch in the IDT
