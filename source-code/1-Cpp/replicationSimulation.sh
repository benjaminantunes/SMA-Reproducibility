#!/bin/bash


for i in `seq 0 $(($2 -1))`;
do
    time ./exe mts10p9N00000$i  $1 log$param$i.txt&
done
wait
