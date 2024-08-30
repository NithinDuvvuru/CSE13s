CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
OBJS = bitreader.o bitwriter.o node.o pq.o
HEAD = bitreader.h bitwriter.h node.h pq.h
EXEC=bwtest brtest nodetest pqtest huff dehuff

.PHONY: all clean format scan-build

all: $(EXEC)

bwtest: bwtest.o bitwriter.o
	$(CC) -o bwtest bwtest.o bitwriter.o

brtest: brtest.o bitreader.o
	$(CC) -o brtest brtest.o bitreader.o

nodetest: nodetest.o node.o
	$(CC) -o nodetest nodetest.o node.o

pqtest: pqtest.o pq.o node.o
	$(CC) -o pqtest pqtest.o pq.o node.o

tests: all
	./bwtest
	./brtest
	./nodetest
	./pqtest
	./runtests.sh

huff: huff.o $(OBJS)
	$(CC) $(CFLAGS) -o huff huff.o $(OBJS)

dehuff: dehuff.o $(OBJS)
	$(CC) $(CFLAGS) -o dehuff dehuff.o $(OBJS)

%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) *.o

scan-build: clean
	scan-build --use-cc=clang make

format:
	clang-format -i -style=file *.[ch]
