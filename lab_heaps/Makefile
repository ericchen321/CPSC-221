CXX = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread

OBJS_DIR = .objs

EXE = testheap
OBJS = testheap.o coloredout.o

all: nonasan
nonasan: $(EXE)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@


# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(EXE):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	-rm -rf doc *.o $(EXE) $(OBJS_DIR)

.PHONY: all doc clean nonasan
