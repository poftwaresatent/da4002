#
# msort-example-NlogN.plot
#
# List of gnuplot commands for producing a plot that compares
# theoretical Big-Oh complexity with actual runtime measurements. It
# uses data from the file msort-example.data (which contains runtime
# measurements from 5 runs), but it divides each time by N*log(N),
# because merge sort has a theoretical runtime complexity of O(N log
# N). In order to see the plot, either copy-paste each line into an
# interactive gnuplot session (which you get by starting gnuplot by
# itself in a terminal), or execute the following command:
#
#   gnuplot -persist msort-example-NlogN.plot
#
# Notice the "-persist" option, which keeps the figure window open
# after gnuplot exits.
#

O(N) = N * log(N)
set key left
set title 'merge sort on random data, convergence for O(N log N)'
set ylabel 'time [ms] / (N log N)'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
plot 'msort-example.data' u 1:($7/O($1)) w lp t 'min', 'msort-example.data' u 1:($8/O($1)) w lp t 'avg', 'msort-example.data' u 1:($9/O($1)) w lp t 'max'
