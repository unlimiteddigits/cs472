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

// http://faculty.salina.k-state.edu/tim/ossg/IPC_sync/ts.html
// http://enggedu.com/tamilnadu/university_questions/question_answer/be_nd_2007/5th_sem/cse/cs1252/part_b/12_b_1.html
void signal (semaphore S);
void wait(semaphore S);

struct semaphore {
    int value = 0;
    boolean mutex = FALSE;
    boolean hold = TRUE;
    queue m, h;
};

struct semaphore s;

int main(int argc, char *argv[]){
	
}

void wait(semaphore S){
	S.value--;
	if(S.value<0){
		add this process to S.L;
		block();
	}
}

void signal (semaphore S){
	S.value++;
	if(S.value <= 0){
		remove a process P from S.L;
		wakeup(P);
	}
}

/* P() */
/*
acquire_semaphore(struct semaphore s) {
    while(TS(s.mutex)) WAIT(s.m);    // wait for intertal mutex 
    s.value--;
    if(s.value < 0) {
        s.mutex = FALSE;
        SIGNAL(s.m);
        while(TS(s.hold)) WAIT(s.h); // wait - too many out 
    }
    else
        s.mutex = FALSE;
        SIGNAL(s.m);
}

/* V() */
/*
release_semaphore(struct semaphore s) {
    while(TS(s.mutex)) WAIT(s.m);   // wait for intertal mutex 
    s.value++;
    if(s.value >= 0) {
        s.hold = FALSE;
        SIGNAL(s.h);
    }
    s.mutex = FALSE;
    SIGNAL(s.m);
}
*/
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
