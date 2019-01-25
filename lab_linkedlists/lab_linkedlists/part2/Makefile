all : lists 

linked_list.o : linked_list.cpp linked_list.h
	g++ -Wall -g -c linked_list.cpp -o linked_list.o

lists.o : lists.cpp linked_list.h
	g++ -std=c++11 -Wall -g -c lists.cpp -o lists.o

lists : lists.o linked_list.o
	g++ -Wall -g lists.o linked_list.o -o lists 

clean :
	rm -f linked_list.o lists.o lists
 
