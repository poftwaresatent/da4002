set key left
set title 'merge sort on random data'
set ylabel 'time [ms]'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
set term png
set output 'msort-example.png'
plot 'msort-example.data' u 1:7 w lp t 'min', 'msort-example.data' u 1:8 w lp t 'avg', 'msort-example.data' u 1:9 w lp t 'max'
