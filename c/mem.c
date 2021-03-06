/* mem.c : memory manager
 */

#include <xeroskernel.h>
#include <i386.h>
extern long freemem;
char *maxaddr;
int returnErr = -1;

struct memHeader *memSlot;

//Initialize mem, two large nodes with hole in between.
//only initialize free memory
void kmeminit(void){
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

  //kprintf("\nfreemem: %d, memSlotSize: %d, memSlotNextSize: %d, memSlotNext: %d\n", freemem, memSlot->size, memSlot->next->size, memSlot->next);
}

//shows free mem nodes
void printNodes(){
	struct memHeader *temp = memSlot;
	int nodeCount = 0;
	while(temp->next != NULL){
		temp=temp->next;
		nodeCount++;
	}
}



//give set amount of free mem
//a new node is created at the end of given memory
//then added to the existing free nodes.
void* kmalloc(int size){

	//asking too much
	if(size>2531327){
		return -1;
	}

	int *returnVal = &returnErr;
	struct memHeader *temp = memSlot;
	//convert sizeWithHeader to 16 bit boundary
	long sizeIn16 = 1 + (size/16) + ((size%16)?1:0); //convert to count of 16 bits
	long sizeWithHeader = sizeIn16*16; //converts back to bits and adds header size

	//iterate to find node with enough RAM
	while(temp->next != NULL){ 
		if(temp->size >= sizeWithHeader){
			break; 
		}
		if((temp->next == NULL) && (temp->size<sizeWithHeader)){
			return returnVal; //not enough RAM
		}
		//move pointer if mem less than size
		temp = temp->next;

	}

	//give portion of node if there is enough space for another node
	if((temp->size - sizeWithHeader)>20){ //minimum 4bytes left over -> 16+4?
		struct memHeader *newNode = (struct memHeader *)(temp + sizeIn16); //new node with free RAM
		//kprintf("<temp:%d*newNode:%d*>",temp,newNode);

		if(temp->prev == NULL){ //if head
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
			temp->prev->next = newNode;

			newNode->next = NULL;

			newNode->prev = temp->prev;
			newNode->size = (temp->size) - sizeWithHeader;
			newNode->sanityCheck = "pizzapizza";

			temp->next = NULL;
			temp->prev = NULL;
			temp->size = sizeWithHeader-16;


			return temp;
		}else{ //middle node
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
		return -1;
	}

	return -1; //error
}

//puts freed memory back into the free pool
extern void kfree(void *ptr) {
	//first check that ptr is valid
	char *c = "pizzapizza";
	struct memHeader *p = (struct memHeader*)ptr;
	if (p->sanityCheck != c) {
		kprintf(" invalid memory header\n");
		return;
	}
	//add node into freenodes
	struct memHeader *temp = memSlot;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next->next = p;
	kprintf(" sucessfully readded mem\n");
}

