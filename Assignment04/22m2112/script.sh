#!bin/bash

gcc load_gen.c -o load

for usercnt in  5000
do
    taskset -a -c 1 ./load localhost 8000 $usercnt 0.1 30 | grep FINAL_OUTPUT >> dataresult.csv
done

