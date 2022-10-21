OBJS = Main.o Partition.o

Main.o: Main.cpp
	g++ -c Main.cpp

Partition.o: Partition.cpp
	g++ -c Partition.cpp

program: clean $(OBJS)
	g++ -o program.o $(OBJS)
	make run

run:
	./program
clean:
	rm -rf ./program
	rm -rf ./Main.o
	rm -rf ./Partition.o
