#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
pid_t pid, pid1, pid2, pid3;
/* fork a child process */
pid = fork();
pid2= getpid();
pid3= getpid();
printf("pid2=%d\tpid3=%d\n",pid2,pid3);

if (pid < 0) { /* error occurred */
      fprintf(stderr, "Fork Failed");
      return 1;
}
else if (pid == 0) { /* child process */
      pid1 = getpid();
      printf("child: pid = %d\n",pid); /* A */
      printf("child: pid1 = %d\n",pid1); /* B */
}
else { /* parent process */
      pid1 = getpid();
      printf("parent: pid = %d\n",pid); /* C */
      printf("parent: pid1 = %d\n",pid1); /* D */
      wait(NULL);
}
return 0;
}
