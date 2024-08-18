.PHONY: all clean test cpplint cppcheck leaks gcov_report rebuild
CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17
TEST_FLAGS = -lgtest -pthread --coverage 
GTEST_FLAGS = -lgtest
GCOV_FLAG = -fprofile-arcs -ftest-coverage 
TESTFILE=test

OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
else
	LIBFLAGS=-lstdc++ -lm -lgtest
endif

test:
	$(CC) $(FLAGS) tests.cpp  $(TEST_FLAGS) -o $(TESTFILE) > output.log 2>&1
	./$(TESTFILE)

rebuild: clean all

check: leaks cpplint cppcheck gcov_report 

all: $(TESTFILE) check


gcov_report:
	$(CC) $(FLAGS) tests.cpp  $(TEST_FLAGS) -o $(TESTFILE) -o gcov_report --coverage
	./gcov_report
	gcov *s21_*.c
	lcov -d . -o gcov_report.info -c --no-external
	genhtml -o report gcov_report.info
	open report/index.html

cppcheck:
	@echo "****** cppcheck start ******"
	cppcheck --enable=all --suppress=unmatchedSuppression  --suppress=missingIncludeSystem --language=c++ --std=c++17 *.cpp *.h	

style: 
	clang-format --style=google *.cc *.cpp *.hpp *.h -n s21_*/*

styleformat: 
	clang-format --style=google *.cc *.cpp *.hpp *.h -i s21_*/*

clean:
	rm -f *.o *.a *.gcno *.gcda *.info a.out $(TESTFILE)
	rm -rf report/ gcov_report output.log

leaks:
ifeq ($(OS), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TESTFILE)
else
	CK_FORK=no leaks -atExit -- ./$(TESTFILE)
endif
