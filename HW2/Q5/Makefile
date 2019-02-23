
#fib_shm_parent: fib_shm_parent.c fib_shm_child.c
#	g++ -o fib_shm_parent fib_shm_parent.c fib_shm_child.c -I.

TARGETS = q5
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -Werror -pthread

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -o $@
	
clean:
	rm -f $(TARGETS)
	
#  ALL THAT  does this => gcc -Wall -g -std=c99 -Werror fib_shm_parent.c -o fib_shm_parent