EXE = quackfun

OBJS_DIR = .objs

OBJS_STUDENT = main.o exercises.o 
OBJS_TEST = tests/basic.o exercises.o
OBJS_PROVIDED = 

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all: $(EXE)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

################# TEST CODE
test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

clean:
	rm -rf $(EXE) $(OBJS_DIR) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
