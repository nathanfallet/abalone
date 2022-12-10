TARGET_EXEC := abalone

BUILD_DIR := ./build
SRC_DIRS := ./src
TESTS_DIR := ./tests

# Find all the C files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')
TESTS_SRCS := $(shell find $(TESTS_DIR) -name '*.c')

# String substitution for every C file.
# As an example, hello.c turns into ./build/hello.c.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS_FOR_TESTS := $(addsuffix _tests, $(filter-out %/gui.c.o, $(filter-out %/main.c.o, $(OBJS))))
TESTS_OBJS := $(TESTS_SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.c.o turns into ./build/hello.c.d
DEPS := $(OBJS:.o=.d)
TESTS_DEPS := $(TESTS_OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# Default task (Test and compile)
all: clean tests $(TARGET_EXEC)

# The final build step.
$(TARGET_EXEC): $(OBJS)
	gcc -pthread $(OBJS) -o $@ $(LDFLAGS) $$(pkg-config --libs --cflags gtk+-3.0)

# The build step for tests.
tests: $(OBJS) $(TESTS_OBJS)
	gcc -Wall -fprofile-arcs -ftest-coverage -pthread $(OBJS_FOR_TESTS) $(TESTS_OBJS) -o $(TARGET_EXEC)_tests $(LDFLAGS)
	./$(TARGET_EXEC)_tests

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	gcc $(CPPFLAGS) $(CFLAGS) $$(pkg-config --libs --cflags gtk+-3.0) -c $< -o $@
	gcc -fprofile-arcs -ftest-coverage -O0 $(CPPFLAGS) $(CFLAGS) $$(pkg-config --libs --cflags gtk+-3.0) -c $< -o $@_tests

# Generate coverage report
coverage: tests
	gcov -pb $(OBJS)

.PHONY: clean
clean:
	-rm abalone
	-rm abalone_tests
	-rm -r $(BUILD_DIR)
	-rm *.gcov

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
