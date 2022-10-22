OBJS = Main.o Partition.o PartitionedHashJoin.o
EXEC = program

$(EXEC): $(OBJS)
	g++ -o $(EXEC) $(OBJS)
	make run

Main.o: Main.cpp
	g++ -c Main.cpp

Partition.o: Partition.cpp
	g++ -c Partition.cpp

PartitionedHashJoin.o: PartitionedHashJoin.cpp
	g++ -c PartitionedHashJoin.cpp

run:
	./program
clean:
	rm -rf ./program *.o
