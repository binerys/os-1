#ifndef SIMPSH_H
#define SIMPSH_H

/////////////////////////////////
/* GLOBALS */
/////////////////////////////////

// Counters

// Index variable
extern int fd_index;
extern int proc_index;

// Data Structures
typedef struct process {
	pid_t pid; 
	int status;
	char** cmd;
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
#endif