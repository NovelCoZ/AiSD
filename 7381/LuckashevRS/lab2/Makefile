CODE 	= ./Source/
OBJ 	= lab2.o alg_expr.o hlist.o
EXE 	= lab2
CXX		= g++
CFLAGS 	= -Wall -Wextra -fpermissive -c -static

all:  $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

lab2.o: $(CODE)lab2.cpp
	$(CXX) $(CFLAGS) $(CODE)lab2.cpp

alg_expr.o: $(CODE)alg_expr.cpp $(CODE)alg_expr.h
	$(CXX) $(CFLAGS) $(CODE)alg_expr.cpp

hlist.o: $(CODE)hlist.cpp $(CODE)hlist.h $(CODE)hlist_impl.h 
	$(CXX) $(CFLAGS) $(CODE)hlist.cpp	
clean:
	rm $(OBJ) $(EXE)
	