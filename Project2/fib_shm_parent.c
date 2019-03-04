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
	printf("Parent here. \n");
	printf("	My PID %d.\n", getpid());

	int n;
	int shmid;
	key_t key;
	char *shm;
	char *s;
	char singledigit[10];

	if (argc != 2 || atoi(argv[1])<= 0)
	{
		printf("Please provide only one positive number.\n");
		return 0;
	}
	n = atoi(argv[1]);
	
	key=9876;
	int size;

	size = n * sizeof(int);

	//ftruncate(sh_fd, size);
	 
	shmid = shmget(key, size, IPC_CREAT | 0666);
	//ftruncate(key, size);
	if (shmid < 0)
	{
		perror("shmget in parent process.");
		exit(1);
	}
	
	shm=shmat(shmid, NULL,0);
	
	//perror("test perror");

	if (shm ==  (char *) -1)
	{
		perror("shmat in parent process.");
		exit(1);
	}
	
 
	char snum[50];
	sprintf(snum,"%i",n);
	
	memcpy(shm, snum, strlen(snum));

	s = shm;
	
	s += strlen(snum);
	
	*s =0 ;
	
	pid_t pid = fork();
	
	printf("Fork Returned: %d\n", (int) pid);
	
	if (pid < 0 ) {
		perror("Fork Failed");
	}
	
	if (pid==0) {
		char *args[]={"./fib_shm_child", argv[1], NULL};

		// with L: comma separated arguments
		// with V: Vector (i.e., an array of strings)
		// with P: Include normal search path for executable
		// i.e. - execvp(args[0],args);
		execlp(args[0],args[0],args[1]);
	}
	while(*shm == *snum)
		sleep(1);

	printf("Fibonacci sequence = %s\n",shm);

 if ( shmctl( shmid, IPC_RMID, NULL ) == -1 )
         perror("failed to destroy");
	
    printf("Parent End\n\n");
	return 0;
}

