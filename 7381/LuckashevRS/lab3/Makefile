CODE 	= ./Source/
OBJ 	= lab3.o stack.o
EXE 	= lab3
CXX		= g++
CFLAGS 	= -Wall -Wextra -fpermissive -c -static

all:  $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

lab3.o: $(CODE)lab3.cpp
	$(CXX) $(CFLAGS) $(CODE)lab3.cpp

stack.o: $(CODE)stack.cpp $(CODE)stack.h
	$(CXX) $(CFLAGS) $(CODE)stack.cpp

clean:
	rm $(OBJ) $(EXE)
	