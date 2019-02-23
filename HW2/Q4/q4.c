#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
pid_t pid;
/* fork a child process */
pid = fork();

if (pid == 0) { /* child process */
      fork();
      thread create( . . .);
}
fork();

return 0;
}
