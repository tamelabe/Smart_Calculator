.PHONY : clean check tests leaks tests_linux leaks_linux gcov_report

CC = gcc
CPPFLAGS = -ggdb -std=c++17 -pedantic -Wall -Werror -Wextra -lstdc++
TEST_FLAGS = -lgtest --coverage
LINUX_FLAGS = -lrt -lpthread -lm -lsubunit
VG_FLAGS = CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
TESTS = ./tests/main_model_test.cc ./model/main_model.cc

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
all: clean check tests leaks gcov_report
else ifeq ($(OS), Linux)
all: clean check tests_linux leaks_linux gcov_report
else
all:
	@echo "Unsupported operating system: $(OS)"
endif

check:
	cp ../materials/linters/.clang-format .
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -n --style="Google" {} \;
	rm -f .clang-format

tests: clean
	$(CC) $(CPPFLAGS) $(TESTS) -o test.o $(TEST_FLAGS);
	./test.o

tests_linux:


leaks:
	for file in $(shell find . -maxdepth 1 -type f -name "*.o"); do \
   		base_name=$$(basename $$file); \
        file_name=$$(echo $${base_name%_test.o} | tr '[:lower:]' '[:upper:]'); \
   		leaks -atExit --  $$file > ./RESULT_$$file_name.txt; \
    done

leaks_linux:
	for file in $(shell find . -maxdepth 1 -type f -name "*.o"); do \
    		base_name=$$(basename $$file); \
    		file_name=$$(echo $${base_name%_test.o} | tr '[:lower:]' '[:upper:]'); \
    		$(VG_FLAGS) --log-file=RESULT_$$file_name.txt $$file; \
    done

gcov_report:
	lcov -t "test" -o s21_test.info -c -d ./ --no-external
	genhtml ./s21_test.info --output-directory ./report/
	open ./report/index.html

clean:
	@rm -rf report *.txt
	@rm -rf *.gcda *.gcno *.info *.gch *.dSYM
	@rm -rf ../*.idea ../.run ../*.dSYM
	@rm -rf *.a *.o
