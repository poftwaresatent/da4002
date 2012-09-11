set title 'Bonus Task A.1 - BS tree input order dependency'
set xlabel 'input size'
set ylabel 'nodes or path length'
set key left top
set logscale y
plot 'bonus-a-order.data' u 1:6 w lp t 'size (random)', 'bonus-a-order.data' u 1:7 w lp t 'size (sorted)', 'bonus-a-order.data' u 1:8 w lp t 'size (reverse)', 'bonus-a-order.data' u 1:9 w lp t 'size (duplicates)', 'bonus-a-order.data' u 1:10 w lp t 'height (random)', 'bonus-a-order.data' u 1:11 w lp t 'height (sorted)', 'bonus-a-order.data' u 1:12 w lp t 'height (reverse)', 'bonus-a-order.data' u 1:13 w lp t 'height (duplicates)'
