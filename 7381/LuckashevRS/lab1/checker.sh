#!/bin/bash 
touch checker_res.txt
cp /dev/null checker_res.txt
for cfile in Tests/Correct/*; do 
    echo "running test: \"Tests/Correct/$cfile\" "; 
	echo "correct test $cfile:" >>checker_res.txt;
    ./lab1 $cfile >>checker_res.txt; 
	echo " ">>checker_res.txt;
done; 
for icfile in Tests/Incorrect/*; do 
    echo "running test: \"Tests/Incorrect/$icfile\" "; 
	echo "incorrect test $icfile:" >>checker_res.txt; 
    ./lab1 $icfile >>checker_res.txt; 
	echo " ">>checker_res.txt;
done;  
