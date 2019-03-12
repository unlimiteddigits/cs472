#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int compare_and_swap(int *value, int expected, int new_value);
int test_and_set(int *target) ;

int size=100;
int pid, pid1;
int waiting[100];
int n,i,j;
int lock=0;
int key=0;
	int shmid;
	key_t skey;
	int *shm;
	char *s;
char singledigit[10];


int main(int argc, char *argv[])
{
	skey=9876;
	shmid = shmget(skey, size, IPC_CREAT | 0666);
	//ftruncate(key, size);
	if (shmid < 0)
	{
		perror("shmget in parent process.");
		exit(1);
	}
	
	shm=shmat(shmid, NULL,0);
	*shm=1;
	printf("after null%i\n",*shm);
	
	//perror("test perror");

	if (shm == (int* )-1)
	{
		perror("shmat in parent process.");
		exit(1);
	}
	
	printf("%i\n",*shm);
	sleep(2);


	pid = fork();
	if (pid < 0) { /* error occurred */
	  fprintf(stderr, "Fork Failed");
	  return 1;
	}
	else if (pid == 0) { /* child process */
		//shmid = shmget(skey, size,  0666);
		//shm=shmat(shmid, NULL,0);
		pid1 = getpid();
		printf("child: pid = %d\n",pid); /* C */
		printf("child: pid1 = %d\n",pid1); /* D */
		sleep(1);
		printf("proceed after 1st sleep.\n");
		*shm = 0;
		sleep(1);
		printf("proceed after 2nd sleep.%i\n", *shm);
		*shm = 0;
		exit(1);
	}
	else { /* parent process */
	  pid1 = getpid();
	  printf("parent: pid = %d\n",pid); /* C */
	  printf("parent: pid1 = %d\n",pid1); /* D */
//	  wait(NULL);
	}
	
	i=0;
	lock=1;
	do {
		while (test_and_set(&lock)!=0)
		{
			if (*shm == 0) {
				lock=0;
			}
		}
		; /* do nothing */
		printf("in first do.  %i\n",i);
		/* critical section */
		lock = 0;
		i++;
		/* remainder section */
	} while (i<10);	
	
	i=0;
	lock=1;
	*shm=1;
	do {
		while (compare_and_swap(&lock, 0, 1) != 0)
			lock=*shm; /* do nothing */
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
			key = compare_and_swap(&lock,0,1);
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
*//*
Bounded-waiting mutual exclusion with test and set().
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
 if ( shmctl( shmid, IPC_RMID, NULL ) == -1 )
         perror("failed to destroy");

}

int compare_and_swap(int *value, int expected, int new_value) {
	int temp = *value;
	if (*value == expected)
		*value = new_value;
	printf("in compare and swap. %i\n",*shm);
	return temp;
}

int test_and_set(int *target) {
	int rv = *target;
	*target = 1;
	printf("in test and set. %i\n",*shm);
	return rv;
}
