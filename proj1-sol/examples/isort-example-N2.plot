#
# isort-example-N2.plot
#
# List of gnuplot commands for producing a plot that compares
# theoretical Big-Oh complexity with actual runtime measurements. It
# uses data from the file isort-example.data (which contains runtime
# measurements from 5 runs), but it divides each time by N*N, because
# insertion sort has a theoretical runtime complexity of O(N*N). In
# order to see the plot, either copy-paste each line into an
# interactive gnuplot session (which you get by starting gnuplot by
# itself in a terminal), or execute the following command:
#
#   gnuplot -persist isort-example-N2.plot
#
# Notice the "-persist" option, which keeps the figure window open
# after gnuplot exits.
#

O(N) = N * N
set key right
set title 'insertion sort on random data, convergence for O(N^2)'
set ylabel 'time [ms] / (N^2)'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
set yrange [0:2e-6]
plot 'isort-example.data' u 1:($7/O($1)) w lp t 'min', 'isort-example.data' u 1:($8/O($1)) w lp t 'avg', 'isort-example.data' u 1:($9/O($1)) w lp t 'max'
