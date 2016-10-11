/* user.c : User processes
 */

#include <xeroskernel.h>

/* Your code goes here */
void producer(void);
void consumer(void);

//first process
void light(){
	kprintf("Hello, World!"); //I can't believe this is printing


	for(;;){
		sysyield();
	}
}

void producer(void){
	int i;
	for(i=0; i<12; i++){
		kprintf("Happy 101s");
	}
	sysstop();
}

void consumer(void){
	int i;
	for(i=0; i<15; i++){
		kprintf("Birthday UBC");
	}
	sysstop();
}
