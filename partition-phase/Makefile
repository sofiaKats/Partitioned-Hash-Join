OBJS = Main.o Partition.o
EXEC = program

$(EXEC): $(OBJS)
	g++ -o $(EXEC) $(OBJS)
	make run

Main.o: Main.cpp
	g++ -c Main.cpp

Partition.o: Partition.cpp
	g++ -c Partition.cpp

run:
	./program
clean:
	rm -rf ./program
	rm -rf ./Main.o
	rm -rf ./Partition.o
