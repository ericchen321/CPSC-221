CXX = clang++
LD = clang++
CXXFLAGS = -c -g -std=c++1y -stdlib=libc++ -Wall -Wextra -pedantic -MP -MMD
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread

DEMO = graphdemo
DEMO_OBJS = graph.o demo.o

LAB = lab_graphs
LAB_OBJS = tests.o graph.o graph_tools.o dsets.o

OBJS_DIR = objs

all: nonasan
nonasan: $(DEMO) $(LAB)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@


# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(DEMO):
	$(LD) $^ $(LDFLAGS) -o $@
$(LAB):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(DEMO):          $(patsubst %.o, $(OBJS_DIR)/%.o,      $(DEMO_OBJS))
$(LAB):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(LAB_OBJS))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	-rm -rf doc *.o $(DEMO) $(LAB) objs

tidy:
	-rm -f images/*.png
	-rm -rf doc

.PHONY: all doc clean tidy nonasan
