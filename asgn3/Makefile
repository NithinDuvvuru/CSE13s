CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic

all: xd test

xd.o: xd.c
	$(CC) $(CFLAGS) -c xd.c
format:
	clang-format -i -style=file *.[ch]
clean:
	rm -rf xd *.o
test: tests 
	bash runner.sh

.PHONY: all clean format