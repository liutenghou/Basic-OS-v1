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
		kprintf("b:");
		switch (request) {
		case (CREATE):
			create(process->firstFunction);
			break;
		case (YIELD):
			ready(process);
			process = next();
			break;
		case (STOP):
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

	//TODO: work on this next

	return (struct pcb*)30000;
}
