#ifndef SIMPSH_H
#define SIMPSH_H

/////////////////////////////////
/* GLOBALS */
/////////////////////////////////

// Flags

// Data Structures
typedef struct process {
	pid_t pid; 
	int status;
} process;

// Process Array
process	*proc; 
// File Descriptor Array
int *fds; 

/////////////////////////////////
/* FUNCTIONS */
/////////////////////////////////

/*
	initialize: 
	- allocates arrays with appropriate sizes
 */
void initialize(int argc, char** argv);

#endif