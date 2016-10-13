/* create.c : create a process
 */

#include <xeroskernel.h>

/* Your code goes here. */
struct pcb process_array[NUMPROC]; //global, goes in kernel stack
int processCount = 0;

void addToReadyQueue(struct pcb *p);

//initialize the process_array
void initProcessArray(void){
//	int i;
//	for(i=0; i<NUMPROC; i++){
//		process_array[i]->state = STOP;
//	}
	memset(process_array, 0, 16*NUMPROC);

}

//set up the process
//process takes a function pointer for first function
int create(void (*func)(void)){
	//kprintf(" CREATE ");
	//a process consists of a context frame, pcb
	struct pcb *p;
	struct context_frame *cf;
	struct memHeader *mh;
	unsigned int pid;

	mh = kmalloc(PROCSIZE);
	if(mh == -1){
		return -1; //error on kmalloc
	}
	//kprintf("check:%s", mh->sanityCheck);
	cf = (unsigned char*)mh + PROCSIZE; //convert to unsigned char for adding 1bit
	cf = (struct context_frame*)(cf-1); //subtracts size of cf = 11*4 = 44
	//kprintf("cf:%d* mh:%d* PROCSIZE:%d* ", cf, mh, PROCSIZE);

	//set initial values for cf
	cf->edi = 0; //gen purpose
	cf->esi = 0; //gen purpose
	//start at the bottom
	cf->ebp = cf; //set to esp at the start of function, local vars relative to here
	cf->esp = cf; //current top location within stack segment
	//kprintf("cf:%d *", cf->esp);
	//
	cf->ebx = 0; //gen purpose
	cf->edx = 0; //gen purpose
	cf->ecx = 0; //gen purpose
	cf->eax = 0; //gen purpose
	cf->iret_eip = func; //next instruction to be executed
	cf->iret_cs = getCS();
	cf->eflags = 0;

	//kprintf("getCS():%d *func: %d *", cf->iret_cs, func);

	//get the first stopped process, in the begginning will be first one
	int i;
	for(i=0; i<NUMPROC; i++){
		if(process_array[i].state == STOP){
			//kprintf("NEXTPROCESS:%d *", i);
			p = &process_array[i];
			processCount=processCount+1;
			break;
		}
	}

	p->pid = processCount;
	p->sanityCheck = "nemo";
	p->esp = (unsigned long*)cf;
	//kprintf(" pesp:%d * ppid:%d *", p->esp, p->pid);
	p->state = READY; //stopped, ready, waiting, running, setc
	p->parent_pid = 0; //not needed?
	p->ret = NULL; //return address
		//struct CPU cpu_state;
	p->next = NULL;
	p->function; //first function for the process

	//add to ready queue
	addToReadyQueue(p);


	//put the context frame at the end
	return p->pid;
}

void addToReadyQueue(struct pcb *p){
	if (readyQueue == NULL){
		readyQueue = p;
		//kprintf("* ADDTOREADYQUEUEp:%d *", p);
	}else{
		struct pcb *temp = readyQueue;
		while(temp->next != NULL){
			//kprintf("* findspace *");
			temp = temp->next;
		}
		temp->next = p;
	}
}
