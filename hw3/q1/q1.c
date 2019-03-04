#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int compare_and_swap(int *value, int expected, int new_value);
int test_and_set(int *target) ;

int pid, pid1;
int waiting[100];
int n,i,j;
int lock=0;
int key=0;

int main(int argc, char *argv[])
{
	pid = fork();
	if (pid < 0) { /* error occurred */
	  fprintf(stderr, "Fork Failed");
	  return 1;
	}
	else if (pid == 0) { /* child process */
		pid1 = getpid();
	  printf("child: pid = %d\n",pid); /* C */
	  printf("child: pid1 = %d\n",pid1); /* D */
		sleep(2);
		lock = 0;
		sleep(2);
		lock = 0;
		exit(1);
	}
	else { /* parent process */
	  pid1 = getpid();
	  printf("parent: pid = %d\n",pid); /* C */
	  printf("parent: pid1 = %d\n",pid1); /* D */
	  wait(NULL);
	}
	
	i=0;
	do {
		while (test_and_set(&lock)!=0)
		; /* do nothing */
		printf("in first do.  %i\n",i);
		/* critical section */
		lock = 0;
		i++;
		/* remainder section */
	} while (i<10);	
	
	i=0;
	do {
		while (compare_and_swap(&lock, 0, 1) != 0)
		; /* do nothing */
		printf("in second do.  %i\n",i);
		/* critical section */
		lock = 0;
		i++;
		/* remainder section */
	} while (i<10);
/*
	do {
		waiting[i] = 1;
		key = 1;
		while (waiting[i]==1 && key==1)
			key = test_and_set(&lock);
		waiting[i] = 0;
		// * critical section * /
		j = (i + 1) % n;
		while ((j != i) && !waiting[j])
			j = (j + 1) % n;
		if (j == i)
			lock = 0;
		else
			waiting[j] = 0;
		/ * remainder section * /
	} while (1);
*/
}

int compare_and_swap(int *value, int expected, int new_value) {
	int temp = *value;
	if (*value == expected)
		*value = new_value;
	printf("in compare and swap. %i\n",temp);
	return temp;
}

int test_and_set(int *target) {
	int rv = *target;
	*target = true;
	printf("in test and set. %i\n",rv);
	return rv;
}
