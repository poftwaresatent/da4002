#!/bin/bash

for foo in 1 2 3 4 5 6 7 8
do
    ./bstree 4 2 6 1 3 5 7 r $foo | dot -Tx11
done
