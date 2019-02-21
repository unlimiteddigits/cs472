/**
Mark Erickson
CS472 Project 2 Linux Shared Memory
02/14/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHSIZE 500

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char *shm;
	char *s;
	int n;
	char snum[600];
	char singledigit[10];
	int prev_num;
	int current_num;
	int sum_num;
		
	printf("	Child here.  ");
	printf("	My PID %d.\n", getpid());

	key=9876;
	n=atoi(argv[1]);
	int size;

	size = n * sizeof(int);

	//ftruncate(sh_fd, size);
	 	
	shmid = shmget(key, size,  0666);
	//ftruncate(key, size);
	if (shmid < 0)
	{
		perror("shmget in child process");
		exit(1);
	}
		shm=shmat(shmid, NULL,0);
	
	if (shm ==  (char *) -1)
	{
		perror("shmat in child process.");
		exit(1);
	}
	n=atoi(shm);
	printf("\n	Preparing %d of the Fibonacci Numbers.", n);

	strcpy(snum,"0");
	prev_num=0;
	current_num=1;

	if (n>1)
	{
		sprintf(singledigit,", %i", 1);
		strcat (snum, singledigit);
	}

	for(int i=2; i<n; i++)
	{	
		sum_num=current_num+prev_num;
		sprintf(singledigit,", %i", sum_num);
		strcat (snum, singledigit);
		prev_num=current_num;
		current_num=sum_num;
	}
	memcpy(shm, snum, strlen(snum));
	s = shm;
	s += strlen(snum);
	*s =0 ;
	
	printf("\n\n	Done updating shared memory in child process.\n\n");
	//printf("%s",snum);
	
	return 0;

}
