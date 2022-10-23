EXEC = program
OBJS = Main.o Partition.o PartitionedHashJoin.o
CFLAGS = -std=c++11 -Wno-unused-parameter -g -w

$(EXEC): $(OBJS)
	g++ $(CFLAGS) $(OBJS) -o $(EXEC)
	make run

run:
	./program
clean:
	rm -rf ./program *.o
