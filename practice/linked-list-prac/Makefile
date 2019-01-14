EXENAME = linked_list_prac.out
OBJS = main.o node.o reverse.o print.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp node.h
	$(CXX) $(CXXFLAGS) main.cpp 

node.o: node.cpp node.h
	$(CXX) $(CXXFLAGS) node.cpp

clean :
	-rm -f *.o
