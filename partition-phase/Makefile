EXEC = program
OBJS = Main.o Partition.o PartitionedHashJoin.o Parser.o ../hopscotch/src/hopscotch.o ../hopscotch/src/Hashtable.o
CFLAGS = -std=c++11 -Wno-unused-parameter -g -w

$(EXEC): $(OBJS)
	g++ $(CFLAGS) $(OBJS) -o $(EXEC)

run:
	./$(EXEC)
clean:
	rm -rf ./$(EXEC) *.o
