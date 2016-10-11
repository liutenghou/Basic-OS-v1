/* xeroskernel.h - disable, enable, halt, restore, isodd, min, max */

#ifndef XEROSKERNEL_H
#define XEROSKERNEL_H

/* Symbolic constants used throughout Xinu */

typedef	char    Bool;        /* Boolean type                  */
typedef unsigned int size_t; /* Something that can hold the value of
                              * theoretical maximum number of bytes 
                              * addressable in this architecture.
                              */
#define	FALSE   0       /* Boolean constants             */
#define	TRUE    1
#define	EMPTY   (-1)    /* an illegal gpq                */
#define	NULL    0       /* Null pointer for linked lists */
#define	NULLCH '\0'     /* The null character            */


/* Universal return constants */

#define	OK            1         /* system call ok               */
#define	SYSERR       -1         /* system call failed           */
#define	EOF          -2         /* End-of-file (usu. from read)	*/
#define	TIMEOUT      -3         /* time out  (usu. recvtim)     */
#define	INTRMSG      -4         /* keyboard "intr" key pressed	*/
                                /*  (usu. defined as ^B)        */
#define	BLOCKERR     -5         /* non-blocking op would block  */

/* Functions defined by startup code */


void           bzero(void *base, int cnt);
void           bcopy(const void *src, void *dest, unsigned int n);
void           disable(void);
unsigned short getCS(void);
unsigned char  inb(unsigned int);
void           init8259(void);
int            kprintf(char * fmt, ...);
void           lidt(void);
void           outb(unsigned int, unsigned char);
void           set_evec(unsigned int xnum, unsigned long handler);

/* Functions for assignment 1 */

struct memHeader{
  unsigned long size;
  struct memHeader *prev;
  struct memHeader *next;
  char *sanityCheck;
  unsigned char dataStart[0];
};

//sets up to pcb struct
struct pcb{
	int pid;
	unsigned long *esp;
	int state; //stopped, ready, waiting, running, setc
	int parent_pid; //not needed?
	char *sanityCheck;
	int ret;
	//struct CPU cpu_state;
	struct pcb *next;
	void (*firstFunction)(void); //first function for the process
};
//registers on stack
struct context_frame {
	unsigned long edi;
	unsigned long esi;
	unsigned long ebp; //base pointer
	unsigned long esp; //stack pointer
	unsigned long ebx;
	unsigned long edx;
	unsigned long ecx;
	unsigned long eax;
	unsigned long iret_eip;
	unsigned long iret_cs; //use getcs();
	unsigned long eflags;
};

//array of pcbs

#define NUMPROC 256
extern struct pcb process_array[NUMPROC];

#define PROCSIZE 8192
#define CREATE 100
#define YIELD 101
#define STOP 0
#define READY 102


extern char	*maxaddr;	/* max memory address (set in i386.c)	*/
extern void kmeminit(void);
extern void *kmalloc(int size);
extern void kfree(void *ptr);
extern void printNodes(void);
extern void dispatch(void); //dispatcher stuff
extern void ready(struct pcb* p);
extern void cleanup(struct pcb* p);
extern int contextswitch(struct pcb* p);
void initProcessArray(void);
void contextinit(void);
extern int create(void (*func)(void)); //create.c
void light(void); //first process, user
extern int syscall(int call, char *sargs); //syscall.c
extern struct pcb* next(void);
extern unsigned int syscreate( void (*func)(void), int stack );
extern void sysyield( void );
extern void sysstop( void );


/* Anything you add must be between the #define and this comment */
#endif
