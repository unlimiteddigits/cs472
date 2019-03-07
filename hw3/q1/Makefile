
#fib_shm_parent: fib_shm_parent.c fib_shm_child.c
#	g++ -o fib_shm_parent fib_shm_parent.c fib_shm_child.c -I.

TARGETS = q1 test
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -Werror -pthread 
# add this flag for unix -D_SVID_SOURCE 

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -o $@
	
test: q1
	./q1 HI

clean:
	rm -f $(TARGETS)
	
#  ALL THAT  does this => gcc -Wall -g -std=c99 -Werror fib_shm_parent.c -o fib_shm_parent