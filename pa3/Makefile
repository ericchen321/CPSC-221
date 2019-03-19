EXE = pa3
EXETest = pa3test

OBJS_EXE = HSLAPixel.o lodepng.o PNG.o main.o toqutree.o stats.o
OBJS_EXET = HSLAPixel.o lodepng.o PNG.o testComp.o toqutree.o stats.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic 
LD = clang++
#LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm 

all : pa3 pa3test

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

$(EXETest) : $(OBJS_EXET)
	$(LD) $(OBJS_EXET) $(LDFLAGS) -o $(EXETest)

#object files
HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

stats.o : stats.h stats.cpp cs221util/HSLAPixel.h cs221util/PNG.h
	$(CXX) $(CXXFLAGS) stats.cpp -o $@

toqutree.o : toqutree.h toqutree.cpp stats.h cs221util/PNG.h cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) toqutree.cpp -o $@

testComp.o : testComp.cpp cs221util/PNG.h cs221util/HSLAPixel.h toqutree.h
	$(CXX) $(CXXFLAGS) testComp.cpp -o testComp.o

main.o : main.cpp cs221util/PNG.h cs221util/HSLAPixel.h toqutree.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

clean :
	-rm -f *.o $(EXE) $(EXETest)
