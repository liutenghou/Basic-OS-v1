/* mem.c : memory manager
 */

#include <xeroskernel.h>
#include <i386.h>
extern long freemem;
char *maxaddr;

struct memHeader{
  unsigned long size;
  struct memHeader *prev;
  struct memHeader *next;
  char *sanityCheck;
  unsigned char dataStart[0];
};

struct memHeader *memSlot;



//Initialize mem
void kmeminit(void){
  kprintf("\nINSIDE MEM MANAGER\n");

  //set free memory linked list
  memSlot = (struct memHeader *)freemem;
  memSlot->size = HOLESTART-freemem;
  memSlot->next = (struct memHeader *)HOLEEND;
  memSlot->sanityCheck = "pizzahut";

  memSlot->next->prev = (struct memHeader *)memSlot;
  memSlot->next->next = NULL;
  memSlot->next->size = (unsigned long)(maxaddr - HOLEEND);
  memSlot->next->sanityCheck = "pizzahut";


  kprintf("maxaddr: %d, HOLEEND: %d, memSlot->next->size: %d, HOLEEND: %d\n", maxaddr, HOLEEND, memSlot->next->size, HOLEEND);
  

}

//give set amount of free mem
void *kmalloc(int size){
	//check size if available in memSlot
	struct memHeader *m = memSlot;
	for(m; m->size < size; m = m->next){
		//move pointer if mem less than size
	}
	if(m == NULL){
		return -1; //error, not enough RAM
	}

	struct memHeader *returnNode = m;

	//take node out of list
	if(m->prev != NULL){
		m->prev->next = m->next;
	}
	if(m->next != NULL){
		m->next->prev = m->prev;
	}

	//give RAM
	return &returnNode;


}

