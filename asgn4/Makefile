CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm


all: calc test


calc: calc.o stack.o mathlib.o operators.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf calc *.o test *.o

format:
	clang-format -i -style=file *.[ch]

test: tests.o stack.o mathlib.o operators.o
	bash runner.sh
	$(CC) $^ $(LFLAGS) -o $@

.PHONY: all clean format
