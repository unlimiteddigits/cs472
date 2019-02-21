/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the consumer process
 *
 * Figure 3.18
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	printf("Self here.");
	printf("	My PID %d.\n", getpid());

	if (argc != 2 ) {
		printf("Pass only 1 argument as an integer.\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	printf("%d...\n",n);
	
	if (n != 0) {
		char nMinus1[10];
		sprintf(nMinus1, "%d", n-1);
		execlp(argv[0],argv[0],nMinus1,NULL);
	}

	// with L: comma separated arguments
	// with V: Vector (i.e., an array of strings)
	// with P: Include normal search path for executable

	//execvp(args[0],args);
	printf("Done.\n");
	return 0;
}
