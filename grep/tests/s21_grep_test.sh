#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0

./s21_grep -e "[a-z]" Makefile tests/README.md > test21_grep_e.txt
grep -e "[a-z]" Makefile tests/README.md > test_grep_e.txt

DIFF_RES="$(diff test21_grep_e.txt test_grep_e.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "1"
    (( COUNTER_FAIL++ ))
fi



./s21_grep -i "[a-z]" Makefile tests/README.md > test21_grep_i.txt
grep -i "[a-z]" Makefile tests/README.md > test_grep_i.txt
DIFF_RES="$(diff test21_grep_i.txt test_grep_i.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "2"
    (( COUNTER_FAIL++ ))
fi




./s21_grep -vn "[a-z]" Makefile tests/README.md > test21_grep_v.txt
grep -vn "[a-z]" Makefile tests/README.md > test_grep_v.txt
DIFF_RES="$(diff test21_grep_v.txt test_grep_v.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "3"
    (( COUNTER_FAIL++ ))
fi





./s21_grep -c "[a-z]" Makefile tests/README.md > test21_grep_c.txt
grep -c "[a-z]" Makefile tests/README.md > test_grep_c.txt
DIFF_RES="$(diff test21_grep_c.txt test_grep_c.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "4"
    (( COUNTER_FAIL++ ))
fi



./s21_grep -l "[a-z]" Makefile tests/README.md > test21_grep_l.txt
grep -l "[a-z]" Makefile tests/README.md > test_grep_l.txt
diff test21_grep_l.txt test_grep_l.txt
DIFF_RES="$(diff test21_grep_l.txt test_grep_l.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "5"
    (( COUNTER_FAIL++ ))
fi



./s21_grep -n "[a-z]" Makefile tests/README.md > test21_grep_n.txt
grep -n "[a-z]" Makefile tests/README.md > test_grep_n.txt
diff test21_grep_e.txt test_grep_e.txt
DIFF_RES="$(diff test21_grep_e.txt test_grep_e.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "6"
    (( COUNTER_FAIL++ ))
fi



./s21_grep -h "[a-z]" Makefile tests/README.md > test21_grep_h.txt
grep -h "[a-z]" Makefile tests/README.md > test_grep_h.txt
DIFF_RES="$(diff test21_grep_h.txt test_grep_h.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "7"
    (( COUNTER_FAIL++ ))
fi



./s21_grep -s "[a-z]" Makefile tests/README.md > test21_grep_s.txt
grep -s "[a-z]" Makefile tests/README.md > test_grep_s.txt
DIFF_RES="$(diff test21_grep_s.txt test_grep_s.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "8"
    (( COUNTER_FAIL++ ))
fi



./s21_grep -f tests/grep_test_reg.txt Makefile tests/README.md > test21_grep_f.txt
grep -f tests/grep_test_reg.txt Makefile tests/README.md > test_grep_f.txt
DIFF_RES="$(diff test21_grep_f.txt test_grep_f.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "9"
    (( COUNTER_FAIL++ ))
fi




./s21_grep -o "[a-z]" Makefile tests/README.md > test21_grep_o.txt
grep -o "[a-z]" Makefile tests/README.md > test_grep_o.txt
DIFF_RES="$(diff test21_grep_o.txt test_grep_o.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
echo "10"
    (( COUNTER_FAIL++ ))
fi


./s21_grep -iv "[a-z]" Makefile tests/README.md > test21_grep_iv.txt
grep -iv "[a-z]" Makefile tests/README.md > test_grep_iv.txt
DIFF_RES="$(diff test21_grep_iv.txt test_grep_iv.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "11"
    (( COUNTER_FAIL++ ))
fi


./s21_grep -ic "[a-z]" Makefile tests/README.md > test21_grep_ic.txt
grep -ic "[a-z]" Makefile tests/README.md > test_grep_ic.txt
DIFF_RES="$(diff test21_grep_ic.txt test_grep_ic.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "12"
    (( COUNTER_FAIL++ ))
fi

./s21_grep -in "[a-z]" Makefile tests/README.md > test21_grep_in.txt
grep -in "[a-z]" Makefile tests/README.md > test_grep_in.txt
DIFF_RES="$(diff test21_grep_in.txt test_grep_in.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "13"
    (( COUNTER_FAIL++ ))
fi

./s21_grep -no "[a-z]" Makefile tests/README.md > test21_grep_no.txt
grep -no "[a-z]" Makefile tests/README.md > test_grep_no.txt
DIFF_RES="$(diff test21_grep_no.txt test_grep_no.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "14"
    
    (( COUNTER_FAIL++ ))
fi

# Multi flags
	./s21_grep -insh Makefile tests/README.md > test21_grep_inshf.txt
	grep -insh Makefile tests/README.md > test_grep_inshf.txt
    DIFF_RES="$(diff test21_grep_e.txt test_grep_e.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    echo "15"
    (( COUNTER_FAIL++ ))
fi


echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"