valgrind --leak-check=full ./s21_grep -e "[a-z]" Makefile tests/README.md > test 
valgrind --leak-check=full ./s21_grep -i "[a-z]" Makefile tests/README.md > test 
valgrind --leak-check=full ./s21_grep -vn "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -c "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -l "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -n "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -h "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -s "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -f grep_test_reg.txt Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -o "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -iv "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -ic "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -in "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -no "[a-z]" Makefile tests/README.md > test
valgrind --leak-check=full ./s21_grep -insh Makefile tests/README.md > test