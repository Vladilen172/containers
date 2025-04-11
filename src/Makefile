SHELL := /bin/bash
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20
LIBS = -lgtest -pthread
COVERAGE_FLAGS = --coverage
OBJ_COMPILE_FLAGS=
ifeq ($(GCOV),1)
  OBJ_COMPILE_FLAGS += $(COVERAGE_FLAGS)
endif
TEST_DIRS = array list map tree queue set stack vector .
DIRS_WITH_TEMPLATES = list map tree vector
SOURCES := $(wildcard $(addsuffix /tests/*.cc,$(TEST_DIRS)))
OBJECTS := $(patsubst %.cc,obj/%.o,$(notdir $(SOURCES)))
VPATH := $(sort $(dir $(SOURCES)))
TEST_EXEC := exec/test
TEST_COV_EXEC := exec/test_cov
.PHONY: all test test_cov build_cov gcov_report rebuild clean obj_dir
all: test
test: $(TEST_EXEC)
	./$(TEST_EXEC)
$(TEST_EXEC): $(OBJECTS) obj_dir exec_dir
	@echo "Linking test executable..."
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)
build_cov: $(TEST_COV_EXEC)
$(TEST_COV_EXEC): $(OBJECTS) obj_dir exec_dir
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)
obj/%.o: %.cc obj_dir
	$(CC) $(CFLAGS) $(OBJ_COMPILE_FLAGS) -c -o $@ $<
obj_dir:
	@mkdir -p obj
exec_dir:
	@mkdir -p exec
gcov_report: clean
	@echo "Building with coverage flags..."
	$(MAKE) build_cov GCOV=1
	@echo "Running tests to generate coverage data..."
	./$(TEST_COV_EXEC)
	@echo "Generating coverage report..."
	lcov --ignore-errors mismatch --capture --directory . --output-file coverage.info --no-external --ignore-errors source
	lcov --remove coverage.info --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report --ignore-errors source
	@echo "HTML report generated in ./coverage_report/"
	@echo "Open ./coverage_report/index.html in your browser."
rebuild: clean all

clean:
	rm -rf obj exec $(TEST_EXEC) $(TEST_COV_EXEC)
	rm -f *.gcno *.gcda *.gcov coverage.info
	rm -rf coverage_report
	rm -f .clang-format
	rm -rf html latex
.PHONY: clang-format-check clang-format-improve cpplint-check 
FILES_TO_FORMAT := $(foreach dir, $(TEST_DIRS), $(wildcard $(dir)/include/*.h $(dir)/tests/*.cc)) \
   $(foreach dir, $(DIRS_WITH_TEMPLATES), $(wildcard $(dir)/templates/*.tpp)) \
   $(wildcard *.cc *.h)

clang-format-check:
	@echo "Checking code formatting..."
	cp ../materials/linters/.clang-format .
	clang-format -n $(FILES_TO_FORMAT)
	rm -f .clang-format

clang-format-improve:
	@echo "Improving code formatting..."
	cp ../materials/linters/.clang-format .
	clang-format -i $(FILES_TO_FORMAT)
	rm -f .clang-format
.PHONY: docker_run
docker_run:
	docker build -t malchiki .
	docker run --rm -it malchiki
ultimate_check: docs clang-format-check gcov_report
	open coverage_report/index.html
docs:
	doxygen Doxyfile