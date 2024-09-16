CC = gcc
CFLAGS = -Werror -Wall -Wextra -pedantic -std=c11

SRC_TESTS = $(wildcard tests/*.c)
SRC_FILES = $(wildcard functions/*.c functions/ariphmetic/*.c functions/another_functions/*.c functions/compare/*.c functions/convertation/*.c) \

OS = $(shell uname)

ifeq ($(OS), Linux)
	COMPILING_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	COMPILING_FLAGS = -lcheck
endif

all: s21_decimal.a test gcov_report

test: s21_decimal.a
	$(CC) $(SRC_TESTS) tests/test_decimal.h s21_decimal.a $(COMPILING_FLAGS) -o ./tests/test
	./tests/test > test_report.txt || true
	./tests/test

s21_decimal.a: s21_decimal
	ar rcs s21_decimal.a *.o
	rm *.o *.h.gch

s21_decimal:
	$(CC) $(CFLAGS) -c $(SRC_FILES) s21_decimal.h

gcov_report:
	$(CC) -c $(CFLAGS) --coverage $(SRC_FILES)
	$(CC) -c $(CFLAGS) $(SRC_TESTS)
	$(CC) $(CFLAGS) *.o -o ./tests/test $(COMPILING_FLAGS) -lgcov
	./tests/test > test_report.txt || true
	lcov -o decimal_tests.info -c -d .
	genhtml -o report decimal_tests.info
	rm *.o *.gcda *.gcno
	$(OPEN) ./report/index.html

valgrind: test
	valgrind ./tests/test --track-origins=yes --tool=memcheck --leak-check=yes --vgdb=no --max-stackframe=4293952 --leak-check=full --show-leak-kinds=all

style_fix:
	clang-format -i $(SRC_FILES) $(SRC_TESTS) s21_decimal.h

style_check:
	clang-format -n $(SRC_FILES) $(SRC_TESTS) s21_decimal.h

install: install_check install_lcov

install_check:
	sudo apt update
	sudo apt install check

install_lcov:
	sudo apt update
	sudo apt install lcov

clean:
	rm -rf *.out s21_decimal.a tests/test test_report.txt *.gcno \
	*.gcda *.o *.info *h.gch big_decimal/big_decimal.h.gch report

rebuild: clean s21_decimal.a
