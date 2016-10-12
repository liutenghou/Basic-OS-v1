/* user.c : User processes
 */

#include <xeroskernel.h>

/* Your code goes here */
void producer(void);
void consumer(void);

//first process
void root(){
	kprintf("\nHello, World!\n"); //I can't believe this is printing
	//no more using create()
	syscreate(producer);
	syscreate(consumer);
	syscreate(producer);
	syscreate(consumer);
	syscreate(producer);
	syscreate(consumer);
	syscreate(producer);
	syscreate(consumer);
	int i;
	for(;;){ //TODO: change to infinite later
		sysyield();
	}
}

void producer(void){
	int i;
	for(i=0; i<12; i++){
		kprintf("Happy 101s ");
	}
	kprintf("\n");
	sysstop();
}

void consumer(void){
	int i;
	for(i=0; i<15; i++){
		kprintf("Birthday UBC ");
	}
	kprintf("\n");
	sysstop();
}
