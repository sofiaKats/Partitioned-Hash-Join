EXEC = program
OBJS = Main.o Partition.o PartitionedHashJoin.o

$(EXEC): $(OBJS)
	g++ $(OBJS) -o $(EXEC)
	make run

run:
	./program
clean:
	rm -rf ./program *.o
