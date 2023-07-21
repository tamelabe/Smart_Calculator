.PHONY : install uninstall clean dvi dist tests gcov_report check leaks leaks_linux leaks_macos

CC = gcc
CPPFLAGS = -ggdb -std=c++17 -pedantic -Wall -Werror -Wextra -lstdc++
TEST_FLAGS = -lgtest --coverage
LINUX_FLAGS = -lrt -lpthread -lm -lsubunit
VG_FLAGS = CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
TESTS = ./tests/model_test.cc ./model/main_model.cc ./model/credit_model.cc
CURRENT_DIR := $(abspath $(CURDIR))
INSTALL_DIR ?= ~/Desktop/

OS := $(shell uname -s)

all: clean install

install: clean
	mkdir build
	cd build && cmake ../CMakeLists.txt && make
	ifeq ($(OS),Darwin)
		mv TameCalc.app "$(INSTALL_DIR)"
	else
		mv TameCalc "$(INSTALL_DIR)"

uninstall:
	ifeq ($(OS),Darwin)
		rm -f "$(INSTALL_DIR)TameCalc.app"
	else
		rm -f "$(INSTALL_DIR)TameCalc"
	endif

clean:
	@rm -rf report build
	@rm -rf *.gcda *.gcno *.info *.gch *.dSYM .DS_Store
	@rm -rf ../*.idea ../.run ../*.dSYM
	@rm -rf *.a *.o
	@rm -rf build/*
	@rm -rf *.user

dvi:
	ifeq ($(OS),Darwin)
		open ./dvi.html
	else
		xdg-open ./dvi.html
	endif

dist: clean
	mkdir SmartCalc/
	mkdir SmartCalc/src
	cp -r ./* SmartCalc/src
	tar -cvzf SmartCalc.tar.gz SmartCalc
	rm -rf SmartCalc

tests:
	ifeq ($(OS),Darwin)
		$(CC) $(CPPFLAGS) $(TESTS) -o test.o $(TEST_FLAGS);
	else
		$(CC) $(TESTS) $(CPPFLAGS) $(TEST_FLAGS) -o test.o $(LINUX_FLAGS);
	endif
	./test.o

gcov_report: tests
	lcov -t "test"  -o s21_test.info -c -d ./ --no-external --exclude '$(CURRENT_DIR)/resources/*'
	genhtml ./s21_test.info --output-directory ./report/
	ifeq ($(OS),Darwin)
		open ./report/index.html
	else
		xdg-open ./report/index.html
	endif

check:
	cp ../materials/linters/.clang-format .
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -n --style="Google" {} \;
	rm -f .clang-format

leaks:
	ifeq ($(OS),Darwin)
		leaks_macos
	else
		leaks_linux
	endif

leaks_macos:
	leaks -atExit -- ./test.o

leaks_linux:
	$(VG_FLAGS) --log-file=RESULT_VALGRIND.txt ./test.o




