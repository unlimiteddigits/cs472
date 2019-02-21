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
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define NUM_LOOPS 500000000
long long sum = 0;

void counting_function(int offset)
{
	for (int i = 0; i < NUM_LOOPS; i++) 
	{
		sum += offset;
	}
}

int main(void)
{
	counting_function(1);
//	counting_function(-1);
	printf("Sum = %lld\n", sum);
	return(0);
}