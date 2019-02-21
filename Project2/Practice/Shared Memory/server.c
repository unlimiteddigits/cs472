/*
compile both
gcc -o server server.c
gcc -o client client.c

run both using 2 differnt terminals
./server
./client

Check memory
ipcs -m

Clear memory
ipcrm -M 9876
  note: 98976 will look like 0x00002694
 

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHSIZE 100

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char *shm;
	char *s;
	
	key=9876;
	
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	
	if (shmid < 0)
	{
		perror("shmget");
		exit(1);
	}
	
	shm=shmat(shmid, NULL,0);
	
	if (shm ==  (char *) -1)
	{
		perror("shmat");
		exit(1);
	}
	
	memcpy(shm, "Hello World\n", 12);
	
	s = shm;
	
	s += 12;
	
	*s =0 ;
	
	while(*shm != '*')
		sleep(1);
	
	return 0;
}