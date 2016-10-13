/* initialize.c - initproc */

#include <i386.h>
#include <xeroskernel.h>
#include <xeroslib.h>

extern	int	entry( void );  /* start of kernel image, use &start    */
extern	int	end( void );    /* end of kernel image, use &end        */
extern  long	freemem; 	/* start of free memory (set in i386.c) */

/************************************************************************/
/***				NOTE:				      ***/
/***								      ***/
/***   This is where the system begins after the C environment has    ***/
/***   been established.  Interrupts are initially DISABLED.  The     ***/
/***   interrupt table has been initialized with a default handler    ***/
/***								      ***/
/***								      ***/
/************************************************************************/

/*------------------------------------------------------------------------
 *  The init process, this is where it all begins...
 *------------------------------------------------------------------------
 */
void initproc( void )				/* The beginning */
{
  
  char str[1024];
  int a = sizeof(str);
  int b = -69;
  int i; 

  kprintf( "\n\nCPSC 415, 2016W1 \n32 Bit Xeros 0.01 \nLocated at: %x to %x\n", 
	   &entry, &end); 
  
  kprintf("Some sample output to illustrate different types of printing\n\n");

  /* A busy wait to pause things on the screen, Change the value used 
     in the termination condition to control the pause
   */

  for (i = 0; i < 1000000; i++);

  /* Build a string to print) */
  sprintf(str, 
      "This is the number -69 when printed signed %d unsigned %u hex %x and a string %s.\n      Sample printing of 1024 in signed %d, unsigned %u and hex %x.\n\n\n",
	  b, b, b, "Hello", a, a, a);

  /* Print the string */

  kprintf("\n\nThe %dstring is: \"%s\"\n\nThe formula is %d + %d = %d.\n\n\n", 
	  a, str, a, b, a + b);

  for (i = 0; i < 1000000; i++);
  /* or just on its own */
  kprintf(str);

  /* Add your code below this line and before next comment */
  kmeminit();

  printNodes();

  struct memHeader *memLocation = (struct memHeader *)kmalloc(16);
  if(memLocation != -1) kprintf("memLocation: %d, sanityCheck:%s, size:%d\n", memLocation, memLocation->sanityCheck, memLocation->size);
  kfree(memLocation);
  kfree(123);
  struct memHeader *memLocation2 = (struct memHeader *)kmalloc(20);
  if(memLocation2 != -1) kprintf("memLocation: %d, sanityCheck:%s, size:%d\n", memLocation2, memLocation2->sanityCheck, memLocation2->size);
  struct memHeader *memLocation3 = (struct memHeader *)kmalloc(1000000);
  if(memLocation3 != -1) kprintf("memLocation: %d, sanityCheck:%s, size:%d\n", memLocation3, memLocation3->sanityCheck, memLocation3->size);
  struct memHeader *memLocation4 = (struct memHeader *)kmalloc(20000);
  if(memLocation4 != -1) kprintf("memLocation: %d, sanityCheck:%s, size:%d\n", memLocation4, memLocation4->sanityCheck, memLocation4->size);
  struct memHeader *memLocation5 = (struct memHeader *)kmalloc(2000000000);
  if(memLocation5 != -1)kprintf("memLocation: %d, sanityCheck:%s, size:%d\n", memLocation5, memLocation5->sanityCheck, memLocation5->size);


   //the last thing init does is create the first user process, then call dispatch()
   //onto the dispatcher
   kprintf("\n\n");
   initProcessArray();
   create(root); //create the first process

   contextinit();
   dispatch();

  for (i = 0; i < 1000000; i++);
  /* Add all of your code before this comment and after the previous comment */
  /* This code should never be reached after you are done */
  kprintf("\n\nWhen the kernel is working properly ");
  kprintf("this line should never be printed!\n");
  for(;;) ; /* loop forever */
}


