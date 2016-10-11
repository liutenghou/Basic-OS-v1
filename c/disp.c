/* disp.c : dispatcher
 */

#include <xeroskernel.h>

/* Your code goes here */
// note pcb struct in xeroshernel.h

struct pcb *process;
struct pcb *readyQueue;
struct pcb *blockedQueue;
int request = 0;

void dispatch() {

	kprintf("d:");
	for (;;) {
		process = next(); //get next ready process
		request = contextswitch(process);
		kprintf(" backtod:");
		switch (request) {
		case (CREATE):
			kprintf(" CREATE:");
			create(process->firstFunction);
			break;
		case (YIELD):
			kprintf(" YIELD:");
			ready(process);
			process = next();
			break;
		case (STOP):
			kprintf(" STOP:");
			cleanup(process);
			process = next();
			break;
		default:
			break;
		}
	}
}

void ready(struct pcb* p){
	//make process ready
}

void cleanup(struct pcb* p){
	//cleanup process
}

//returns pointer to next ready process
struct pcb* next(){
	struct pcb* p;
	//TODO: work on this next, make into linked list instead of array
	//go through the process_array, look for next ready process
	int i;
	for(i=0; i<PROCSIZE; i++){
		if(process_array[i].state == READY){
			p = &process_array[i];
			break;
		}
	}
	//TODO: error for no ready processes

	kprintf(" IN NEXT: ");
	kprintf("p->pid:%d * p->sanityCheck:%s *", p->pid, p->sanityCheck);

	return p;
}
