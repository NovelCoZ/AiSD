#!/bin/bash 
touch checker_res.txt
cp /dev/null checker_res.txt
for cfile in Tests/Correct/*; do 
    echo "running test: \"Tests/Correct/$cfile\" "; 
	echo "correct test $cfile:" >>checker_res.txt;
    ./lab3 $cfile >>checker_res.txt; 
	echo " ">>checker_res.txt;
done; 
