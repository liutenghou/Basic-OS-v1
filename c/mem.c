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
  memSlot->next = HOLEEND;
  memSlot->sanityCheck = 125;

  memSlot->next->prev = memSlot;
  memSlot->next->next = NULL;
  memSlot->next->size = maxaddr - HOLEEND;
  memSlot->next->sanityCheck = 125;


  kprintf("maxaddr: %d, HOLEEND: %d, memSlot->next->size: %d, HOLEEND: %d\n", maxaddr, HOLEEND, memSlot->next->size, HOLEEND);
  

}

