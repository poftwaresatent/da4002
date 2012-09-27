set title 'merge sort runtime on random data'
set xlabel 'array length [N]'
set ylabel 'measured time [ms]'
plot 'msort-example.data' u 1:($2/$1/log($1)) w lp t 'T / (N log N)'
