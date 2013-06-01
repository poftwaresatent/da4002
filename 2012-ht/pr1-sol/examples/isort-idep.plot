set key left
set title 'insertion sort on various data'
set ylabel 'minimum time over 5 runs [ms]'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
plot 'isort-idep.data' u 1:2 w lp t 'random', 'isort-idep.data' u 1:4 w lp t 'ascending', 'isort-idep.data' u 1:6 w lp t 'descending', 'isort-idep.data' u 1:8 w lp t 'mixed'
