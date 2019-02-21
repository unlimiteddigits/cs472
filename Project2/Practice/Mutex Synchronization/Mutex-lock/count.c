/*
compile both
gcc -Wall -g -std=c99 -Werror count.c -o count

run 
./count

time it
time ./count


Check memory
ipcs -m

Clear memory
ipcrm -M 9876
  note: 98976 will look like 0x00002694
 
 

*/
#include <stdio.h>
#include <pthread.h>


#define NUM_LOOPS 2000000
long long sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* counting_function(void *arg)
{
	int offset = *(int *) arg;     // pointer to an int
	for (int i = 0; i < NUM_LOOPS; i++) 
	{
		// start critical section
		pthread_mutex_lock(&mutex);
		sum += offset;
		pthread_mutex_unlock(&mutex);

		// end critical section
	}
	pthread_exit(NULL);
}

int main(void)
{
	//Spawn threads
	
	// was 1 line and now 3 below => counting_function(1);
	pthread_t id2;
	int offset2 = -1;
	pthread_create(&id2, NULL, counting_function, &offset2);
	
	pthread_t id1;
	int offset1 = 1;
	pthread_create(&id1, NULL, counting_function, &offset1);
	
	// wait for threads to finish
	pthread_join(id2, NULL);
	pthread_join(id1, NULL);
	
//	counting_function(-1);
	printf("Sum = %lld\n", sum);
	return(0);
}