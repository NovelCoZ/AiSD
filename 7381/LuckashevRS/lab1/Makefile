CODE 	= ./Source/lab1.cpp
OBJ 	= lab1.o
EXE 	= lab1
CXX		= g++
CFLAGS 	= -Wall -Wextra -c -static

all: $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

$(OBJ): $(CODE)
	$(CXX) $(CFLAGS) $(CODE)

clean:
	rm $(OBJ) $(EXE)
	