#ifndef SIMPSH_H
#define SIMPSH_H

/////////////////////////////////
/* GLOBALS */
/////////////////////////////////

// Counters
extern int procCount;
extern int fdCount;

// Index variable
extern int fd_index;
extern int proc_index;
extern int cmd_index;

// Data Structures
typedef struct process {
	pid_t pid; 
	int status;
	char** cmd; // Points to process's command in commads array
	int cmdCount;  
} process;

extern process	*proc; // Process Array
extern int *fds; // File Descriptor Array
extern char*** commands; // Array of all commandså

/////////////////////////////////
/* FUNCTIONS */
/////////////////////////////////

/*	initialize: 
	- allocates arrays with appropriate sizes
 */
void initialize(int argc, char** argv);

/* terminate:
	- frees all dynamically allocated arrays
 */
void terminate();

int max_exit(int parseExit);
#endif