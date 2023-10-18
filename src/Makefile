# --gtest_brief=1 - to show only test failures

.PHONY: all test clean check style leak
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = g++ -std=c++17
FLAGS = -Wall -Werror -Wextra -lm -lgtest -lstdc++ -lgtest_main
TESTFILES= tests/*.cc

VECTOR = tests/s21_test_vector.cc
MAP = tests/s21_test_map.cc
SET = tests/s21_test_set.cc
MULT = tests/s21_test_mult.cc

LIST = tests/s21_test_list.cc
ARRAY = tests/s21_test_array.cc
QUEUE = tests/s21_test_queue.cc
STACK = tests/s21_test_stack.cc

test: clean vector_test map_test set_test mult_test list_test array_test queue_test stack_test

vector_test:
	$(CC) $(VECTOR) $(FLAGS) -o test_vector
	./test_vector

map_test:
	$(CC) $(MAP) $(FLAGS) -o test_map
	./test_map

set_test:
	$(CC) $(SET) $(FLAGS) -o test_set
	./test_set

mult_test:
	$(CC) $(MULT) $(FLAGS) -o test_mult
	./test_mult

list_test:
	$(CC) $(LIST) $(FLAGS) -o test_list
	./test_list

array_test:
	$(CC) $(ARRAY) $(FLAGS) -o test_array
	./test_array

queue_test:
	$(CC) $(QUEUE) $(FLAGS) -o test_queue
	./test_queue

stack_test:
	$(CC) $(STACK) $(FLAGS) -o test_stack
	./test_stack

gcov_report: clean gcov_test.info
	@genhtml -o report/ gcov_test.info
	@open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test:
	$(CC) $(FLAGS) --coverage $(VECTOR) $(MAP) $(SET) $(MULT) \
	$(LIST) $(ARRAY) $(QUEUE) $(STACK) -o gcov_test

gcov_test.gcda:
	@chmod +x *
	@./gcov_test

clean: 
	@rm -rf *.gch *.out *.o *.a m *.gcda *.gcdo *.gcno *.dSYM coverage_report gcov_test g_test \
	*.html report test_vector test_map test_set test_queue test_array test_stack test_list test_mult GcovReport \
	*.info
	
style:
	cp ../materials/linters/.clang-format ./
	clang-format -n headers/* sources/* tests/* 

leak:
	CK_FORK=no leaks -atExit -- ./test_vector

	CK_FORK=no leaks -atExit -- ./test_map

	CK_FORK=no leaks -atExit -- ./test_set

	CK_FORK=no leaks -atExit -- ./test_mult

	CK_FORK=no leaks -atExit -- ./test_list

	CK_FORK=no leaks -atExit -- ./test_array

	CK_FORK=no leaks -atExit -- ./test_queue

	CK_FORK=no leaks -atExit -- ./test_stack

git:
	git add .
	git commit -m '1'
	git push origin develop

