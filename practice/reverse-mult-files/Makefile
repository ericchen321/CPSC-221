EXENAME = reverse_linked_list.out
OBJS = main.o node.o reverse.o print.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp node.h reverse.h print.h
	$(CXX) $(CXXFLAGS) main.cpp 

node.o: node.cpp node.h
	$(CXX) $(CXXFLAGS) node.cpp

reverse.o: reverse.cpp node.h reverse.h
	$(CXX) $(CXXFLAGS) reverse.cpp

print.o: print.cpp node.h print.h
	$(CXX) $(CXXFLAGS) print.cpp

clean :
	-rm -f *.o
