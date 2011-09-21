#!/bin/bash

echo 'set term' | gnuplot 2>&1 | sed 's/.*://'
