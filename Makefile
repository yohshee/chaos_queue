#
# Makefile for sample program.
#
# Author: Rick Coogle, PhD
#

program=test_queue
source=chaos_queue.c main.c
objs=$(source:%.c=%.o)

$(program): $(objs)
	$(CC) -o $(program) $(objs)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
