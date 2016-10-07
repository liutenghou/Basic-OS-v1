/* create.c : create a process
 */

#include <xeroskernel.h>

/* Your code goes here. */
struct pcb* process_array[NUMPROC]; //global

//set up the process
//process takes a function pointer for first function
int create(void (*func)(void)){
	//a process consists of a context frame, pcb
	struct pcb *p;
	struct context_frame *cf;
	unsigned int pid;

	p = kmalloc(PROCSIZE);
	if(p == maxaddr){
		return -1;
	}


	//get the first stopped process, in the begginning will be first one
	int i;
	for(i=0; i<NUMPROC; i++){
		if(process_array[i]->state == STOP){
			p = process_array[i];
			break;
		}
	}




	//put the context frame at the end



	return 0;
}
