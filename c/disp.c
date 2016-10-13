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

	for (process = next();process;) {

		request = contextswitch(process);
		switch (request) {
		case (CREATE):
			create(process->function);
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

//--> kernel space

//add current process p to ready queue,
int pid = 0;
void ready(struct pcb* p){
	//make process ready
	readyQueue = readyQueue->next;
	readyQueue->state = READY;

	struct pcb* temp = readyQueue;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->state = READY;
	temp->next = p;
}

//cleanup current process p
//remove next process on ready queue to run
void cleanup(struct pcb* p){
	//cleanup process
	p->state = STOP;

}

//returns pointer to next ready process
struct pcb* next(){
	struct pcb* temp = readyQueue;

	if(readyQueue->next == NULL){
		return readyQueue; //no more processes
	}
	readyQueue = readyQueue->next;
	return temp;
}
