/* mem.c : memory manager
 */

#include <xeroskernel.h>
#include <i386.h>
extern long freemem;
char *maxaddr;

struct memHeader *memSlot;

//Initialize mem, two large nodes with hole in between.
//only initialize free memory
void kmeminit(void){
  //kprintf("\nINSIDE MEM MANAGER\n");

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

  //kprintf("freemem: %d, memSlotSize: %d, memSlotNextSize: %d, memSlotNext: %d\n", freemem, memSlot->size, memSlot->next->size, memSlot->next);
}

//shows free mem nodes
void printNodes(){
	struct memHeader *temp = memSlot;
	int nodeCount = 0;
	while(temp->next != NULL){
		//kprintf("n:%dsize:%d|", nodeCount,temp->size);
		temp=temp->next;
		nodeCount++;
	}
	//kprintf("n:%dsize:%d|", nodeCount,temp->size);
}



//give set amount of free mem
//a new node is created at the end of given memory
//then added to the existing free nodes.
void *kmalloc(int size){

	struct memHeader *temp = memSlot;
	// kprintf("temp:%d.memSlot:%d.",temp,memSlot);

	//kprintf("RequestedSize:%d*",size);
	//convert sizeWithHeader to 16 bit boundary
	long sizeIn16 = 1 + (size/16) + ((size%16)?1:0); //convert to count of 16 bits
	long sizeWithHeader = sizeIn16*16; //converts back to bits and adds header size
	//kprintf("sizeWithHeader:%d*",sizeWithHeader);

//	kprintf("sizeWithHeader:%d",sizeWithHeader);
	//iterate to find node with enough RAM
	while(temp->next != NULL){ 
//		kprintf("*temp->size:%d*sizeWithHeader:%d*", temp->size, sizeWithHeader);
		if(temp->size >= sizeWithHeader){
			//kprintf(">");
			break; 
		}
		//move pointer if mem less than size
		temp = temp->next;
		//kprintf("nextTempsize:%d*temp:%d*",temp->size,temp);

	}
	if(temp == NULL){
		return maxaddr; //error, not enough RAM
	}

	//give portion of node if there is enough space for another node
	if((temp->size - sizeWithHeader)>20){ //minimum 4bytes left over -> 16+4?
		struct memHeader *newNode = (struct memHeader *)(temp + sizeIn16); //new node with free RAM
		//kprintf("<temp:%d*newNode:%d*>",temp,newNode);

		if(temp->prev == NULL){ //if head
			//kprintf("HEAD");
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
			//kprintf("TAIL");
			temp->prev->next = newNode;

			//kprintf("BROKE1 newNode:%d*tempPrevNext:%d",newNode,temp->prev->next);
			newNode->next = NULL;

//			kprintf("BROKE2");
			newNode->prev = temp->prev;
			newNode->size = (temp->size) - sizeWithHeader;
			newNode->sanityCheck = "pizzapizza";

			temp->next = NULL;
			temp->prev = NULL;
			temp->size = sizeWithHeader-16;


			return temp;
		}else{ //middle node
			//kprintf("MIDDLE");
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

