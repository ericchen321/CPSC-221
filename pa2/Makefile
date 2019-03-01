TESTSQ = testStackQueue
TESTFILLS = testFills

OBJS_FILLS_STUDENT = testFills.o borderColorPicker.o stripeColorPicker.o  customColorPicker.o
OBJS_FILLS_PROVIDED = animation.o PNG.o HSLAPixel.o lodepng.o rainbowColorPicker.o 
OBJS_SQ = testStackQueue.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all: $(TESTSQ) $(TESTFILLS)

$(TESTSQ) : $(OBJS_SQ)
	$(LD) $(OBJS_SQ) $(LDFLAGS) -o $(TESTSQ)

$(TESTFILLS) : $(OBJS_FILLS_STUDENT) $(OBJS_FILLS_PROVIDED)
	$(LD) $(OBJS_FILLS_STUDENT) $(OBJS_FILLS_PROVIDED) $(LDFLAGS) -o $(TESTFILLS)

testStackQueue.o : testStackQueue.cpp cs221util/PNG.h cs221util/HSLAPixel.h stack.h queue.h deque.h
	$(CXX) $(CXXFLAGS) testStackQueue.cpp

testFills.o : testFills.cpp cs221util/PNG.h cs221util/HSLAPixel.h stack.h queue.h deque.h filler.h filler.cpp rainbowColorPicker.h stripeColorPicker.h borderColorPicker.h customColorPicker.h
	$(CXX) $(CXXFLAGS) testFills.cpp

# Pattern rules for object files
%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean:
	rm -rf $(TESTSQ) $(TESTFILLS) $(OBJS_DIR) *.o

