#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

pthread_t *thread;

pthread_attr_t *attr;

                          void *(*start_routine) (void *), void *arg);


int main()
{
pid_t pid;
/* fork a child process */
pid = fork();

if (pid == 0) { /* child process */
      fork();
      pthread_create(*thread, *attr, "./q4", "");
}
fork();

return 0;
}
