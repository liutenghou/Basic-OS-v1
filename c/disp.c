/* disp.c : dispatcher
 */

#include <xeroskernel.h>

/* Your code goes here */
// note pcb struct in xeroshernel.h

struct pcb* process;
int request = 0;

void dispatch() {
	for (;;) {
		request = contextswitch(process);
		switch (request) {
		case CREATE:
			create();
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

struct pcb* next(){
	return (struct pcb*)0;
}
