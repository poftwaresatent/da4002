set title 'Bonus Task A.1 - BS tree input order dependency'
set xlabel 'input size'
set ylabel 'time for insertion [ms]'
set key left top
set logscale y
plot 'bonus-a-order.data' u 1:2 w lp t 'random', 'bonus-a-order.data' u 1:3 w lp t 'sorted', 'bonus-a-order.data' u 1:4 w lp t 'reverse', 'bonus-a-order.data' u 1:5 w lp t 'duplicates'
