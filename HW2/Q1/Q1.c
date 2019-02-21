#include <stdio.h>
#include <unistd.h>
int main()
{
	int i;
	int count=0;
	for (i = 0; i < 5; i++)
	{
		fork();
		printf("My ID is %d\n", getpid());
		count++;
	}
	//printf("Count=%i\n",count);
	sleep(1);
	
	return 0;
}
