.PHONY: all s21_cat test check clean

CC= gcc
CFLAGS= -Wall -Wextra -Werror -std=c11
SOURCE = s21_grep.c
GREP_EXEC = s21_grep


all: s21_grep
	
s21_grep:
	$(CC) $(CFLAGS) $(SOURCE) -o $(GREP_EXEC)

test: s21_grep
	bash tests/s21_grep_test.sh

check: s21_grep
	cppcheck --enable=all --force --check-config for details *.c *.h
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n $(SOURCE)

clean:
	rm -f $(GREP_EXEC) .clang-format log.txt
	rm -f test_grep_* test21_grep_* 
	
