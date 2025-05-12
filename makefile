EXCLUDE = ext_commands.txt
SRCS = $(filter-out $(EXCLUDE), $(wildcard *.c))
OBJS = $(patsubst %.c,%.o,$(SRCS))

a.out: $(OBJS)
	gcc -o $@ $^

clean:
	rm *.o