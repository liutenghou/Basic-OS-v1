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
  //TODO: initialize the process queue


  kprintf( "\n\nCPSC 415, 2016W1 \n32 Bit Xeros 0.01 \nLocated at: %x to %x\n", 
	   &entry, &end); 
  
  kprintf("Some sample output to illustrate different types of printing\n\n");

  /* A busy wait to pause things on the screen, Change the value used 
     in the termination condition to control the pause
   */

  for (i = 0; i < 1000000; i++);

  /* Build a string to print) */
  sprintf(str, 
      "This is the number -69 when printed signed %d unsigned %u hex %x and a string %s.\n      Sample printing of 1024 in signed %d, unsigned %u and hex %x.",
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

//  long *memLocation = (long *)kmalloc(16);
  //kprintf("memLocation: %d", memLocation);
//  long *memLocation2 = (long *)kmalloc(20);
  // kprintf("memLocation: %d", memLocation2);
//  long *memLocation3 = (long *)kmalloc(1000000);
  // kprintf("memLocation: %d", memLocation3);
//   long *memLocation4 = (long *)kmalloc(20000);
  // kprintf("memLocation: %d", memLocation4);
  // long *memLocation5 = (long *)kmalloc(20000);
  // kprintf("memLocation: %d", memLocation5);
  // long *memLocation6 = (long *)kmalloc(200000);
  // kprintf("memLocation: %d", memLocation6);

   //TODO: the last thing init does is create the first user process, then call dispatch()
   //onto the dispatcher
   kprintf("\n\n");
   create(light); //create the first process
   //dispatch();


  for (i = 0; i < 1000000; i++);
  /* Add all of your code before this comment and after the previous comment */
  /* This code should never be reached after you are done */
  kprintf("\n\nWhen the kernel is working properly ");
  kprintf("this line should never be printed!\n");
  for(;;) ; /* loop forever */
}


