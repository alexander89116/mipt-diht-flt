#!/bin/bash

readonly TEST_COUNT=$(ls tests/ | wc -l);

g++ main.cpp -o test

for (( i = 0; i < TEST_COUNT; i++))
do
    ./test <tests/$i/in  >tests/$i/out1
    echo "Test $i:"
    cat tests/$i/in
    cat tests/$i/out
    if  (diff tests/$i/out tests/$i/out1); then
        echo "Test result: Ok"
    else
        echo "Test result: WA"
    fi
    rm tests/$i/out1
    echo
done

rm test


