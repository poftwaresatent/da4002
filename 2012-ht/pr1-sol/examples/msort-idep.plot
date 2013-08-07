set key left
set title 'merge sort on various data'
set ylabel 'minimum time over 5 runs [ms]'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
#set term png
#set output 'msort-idep.png'
plot 'msort-idep.data' u 1:2 w lp t 'random', 'msort-idep.data' u 1:4 w lp t 'ascending', 'msort-idep.data' u 1:6 w lp t 'descending', 'msort-idep.data' u 1:8 w lp t 'mixed'
