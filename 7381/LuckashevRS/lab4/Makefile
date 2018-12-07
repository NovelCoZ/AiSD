CODE 	= ./Source/
OBJ 	= lab4.o queue.o bintree.o
EXE 	= lab3
CXX		= g++
CFLAGS 	= -Wall -Wextra -fpermissive -c -static

all:  $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

lab4.o: $(CODE)lab4.cpp
	$(CXX) $(CFLAGS) $(CODE)lab4.cpp

queue.o: $(CODE)queue.cpp $(CODE)queue.h
	$(CXX) $(CFLAGS) $(CODE)queue.cpp
	
bintree.o: $(CODE)bintree.cpp $(CODE)bintree.h
	$(CXX) $(CFLAGS) $(CODE)bintree.cpp

clean:
	rm $(OBJ) $(EXE)
	