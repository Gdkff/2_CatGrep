.PHONY: all s21_cat test check clean

CC= gcc
CFLAGS= -Wall -Wextra -Werror -std=c11
SOURCE = s21_cat.c
CAT_EXEC = s21_cat
CAT_TEST_EXEC = tests/cat_test.out

LIBS_ADDITIONAL = 
ifeq ($(OS), Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

ifeq ($(detected_OS), Linux)
	detected_Linux := $(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')
	ifeq ($(detected_Linux), Arch)
	LIBS_ADDITIONAL = -lm
	endif

	ifeq ($(detected_Linux), Ubuntu)
	LIBS_ADDITIONAL = -lm -lsubunit
	endif
	
	ifeq ($(detected_Linux), Debian)
	LIBS_ADDITIONAL = -lm -lsubunit
	endif
endif

all: s21_cat
	
s21_cat:
	$(CC) $(CFLAGS) $(SOURCE) -o $(CAT_EXEC)

test: s21_cat
	bash tests/t_cat.sh
#	$(CC) $(CFLAGS) tests/cat_test.c -o $(CAT_TEST_EXEC) -lcheck $(LIBS_ADDITIONAL)
#	./$(CAT_TEST_EXEC)


check:
	cppcheck --enable=all --force --check-config for details *.c *.h
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n $(SOURCE)

clean:
	rm -f $(CAT_EXEC) $(CAT_TEST_EXEC) log.txt .clang-format
	rm -rf tests/cat_txt
