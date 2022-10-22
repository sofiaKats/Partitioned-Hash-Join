SRC = ./src

# .o files will be stored here
BLD = ./obj

# Compiler options
CC = g++
CFLAGS = -std=c++11 -Wno-unused-parameter -g -w

# Executable file names
EXE_HOPSCOTCH = ./hopscotch

# .o files needed
OBJS_HOPSCOTCH =  $(SRC)/hopscotch.o $(SRC)/main.o

# Build executables
all: $(EXE_HOPSCOTCH)
	mkdir -p $(BLD)
	mv -f $(OBJS_HOPSCOTCH) $(BLD)

$(EXE_HOPSCOTCH): $(OBJS_HOPSCOTCH)
	$(CC) $(CFLAGS) $(OBJS_HOPSCOTCH) -o $(EXE_HOPSCOTCH)

# Delete executable & object files
clean:
	rm -f $(EXE_HOPSCOTCH)
	rm -rf $(BLD)

# Clean and compile
comp: clean all