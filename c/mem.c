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
  memSlot->prev = NULL;
  memSlot->next = (struct memHeader *)HOLEEND;
  memSlot->sanityCheck = "pizzapizza";

  memSlot->next->prev = memSlot;
  memSlot->next->next = NULL;
  memSlot->next->size = (unsigned long)(maxaddr - HOLEEND);
  memSlot->next->sanityCheck = "pizzapizza";

  kprintf("freemem: %d, HOLEEND: %d, memSlot->prev: %d, sanityCheck: %s\n", freemem, HOLEEND, memSlot->prev, memSlot->sanityCheck);  

}

//shows free mem nodes
void printNodes(){
	struct memHeader *temp = memSlot;
	while(temp->next != NULL){
		kprintf("temp->size,%d|", temp->size);
		temp=temp->next;
	}
	kprintf("temp->size, %d", temp->size);
}

//give set amount of free mem
//NOTE: memory address returned is beginning of node, need to add 16
void *kmalloc(int size){

	struct memHeader *temp = memSlot;
	// kprintf("temp:%d.memSlot:%d.",temp,memSlot);

	//check size if available in memSlot
	//check size + size of struct 16bits
	int sizeWithHeader = size + 16;
	// kprintf("sizeWithHeader:%d",sizeWithHeader);
	//iterate to find node with enough RAM
	while(temp->next != NULL){ 
		kprintf("*temp->size:%d.sizeWithHeader:%d*", temp->size, sizeWithHeader);
		if(temp->size >= sizeWithHeader){
			kprintf(">");
			break; 
		}
		//move pointer if mem less than size
		temp = temp->next;
		kprintf("nextTempsize:%d*temp:%d*",temp->size,temp);
		kprintf("()");
	}
	if(temp == NULL){
		return maxaddr; //error, not enough RAM
	}

	//give portion of node if there is enough space for another node
	if((temp->size - sizeWithHeader)>20){ //minimum 4bytes left over -> 16+4?
		struct memHeader *newNode = (struct memHeader *)(temp + sizeWithHeader); //new node with free RAM
		// kprintf("temp->prev:%d",temp->prev);

		//TODO: fix logic
		if(temp->prev == NULL){ //if head
			kprintf("HEAD");
			temp->next->prev = newNode;

			newNode->prev = NULL;
			newNode->next = temp->next;
			newNode->size = (temp->size) - sizeWithHeader;
			newNode->sanityCheck = "pizzapizza";
			memSlot = newNode;

			temp->next = NULL;
			temp->prev = NULL;
			temp->size = sizeWithHeader-16; 

			return temp;
		}else if(temp->next == NULL){ //tail
			kprintf("TAIL");
			temp->prev->next = newNode;

			kprintf("BROKE1. pointer:%d",&newNode);
			newNode->next = NULL;

			kprintf("BROKE2");
			newNode->prev = temp->prev;
			newNode->size = (temp->size) - sizeWithHeader;
			newNode->sanityCheck = "pizzapizza";

			temp->next = NULL;
			temp->prev = NULL;
			temp->size = sizeWithHeader-16;


			return temp;
		}else{ //middle node
			kprintf("MIDDLE");
			temp->next->prev = newNode;
			temp->prev->next = newNode;

			newNode->next = temp->next;
			newNode->prev = temp->prev;
			newNode->size = (temp->size) - sizeWithHeader;
			newNode->sanityCheck = "pizzapizza";

			temp->next = NULL;
			temp->prev = NULL;
			temp->size = sizeWithHeader-16;

			return temp;
		}
	}else{ //give the whole node
		return maxaddr;
	}

	return maxaddr;
}

