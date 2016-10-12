/* disp.c : dispatcher
 */

#include <xeroskernel.h>

/* Your code goes here */
// note pcb struct in xeroshernel.h
// kernel space

struct pcb *process;
struct pcb *blockedQueue;
int request = 0;

void dispatch() {

	kprintf("d:");
	for (;;) {

		process = next(); //get next ready process
		request = contextswitch(process);
		//kprintf(" backtod:");
		switch (request) {
		case (CREATE):
			kprintf(" 4CREATE:p->f:%d, p->pid:%d *", process->function, process->pid);
			create(process->function);
			break;
		case (YIELD):
			kprintf(" 2YIELD:");
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

//--> kernel space

//add current process p to ready queue,
//remove next process on ready queue to run
void ready(struct pcb* p){
	//make process ready
	readyQueue = readyQueue->next;
	readyQueue->state = READY;

	struct pcb* temp = readyQueue;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = p;
}

//cleanup current process p
//remove next process on ready queue to run
void cleanup(struct pcb* p){
	//cleanup process
}

//returns pointer to next ready process
struct pcb* next(){
	struct pcb* temp = readyQueue;
	kprintf("* temp:%d *", temp);
	//TODO: work on this next, make into linked list instead of array
	//go through the process_array, look for next ready process
//	int i;
//	for(i=0; i<PROCSIZE; i++){
//		if(process_array[i].state == READY){
//			p = &process_array[i];
//			break;
//		}
//	}
	//TODO: error for no ready processes
	while(temp->next != NULL){
		if(temp->state == READY){
			break;
		}
	}

	//kprintf(" IN NEXT: ");
	//kprintf("p->pid:%d * p->sanityCheck:%s *", p->pid, p->sanityCheck);

	return temp;
}
