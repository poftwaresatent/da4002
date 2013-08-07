#
# isort-example.plot
#
# List of gnuplot commands which plot data from the file
# isort-example.data (which contains runtime measurements from 5
# runs). In order to see the plot, either copy-paste each line into an
# interactive gnuplot session (which you get by starting gnuplot by
# itself in a terminal), or execute the following command:
#
#   gnuplot -persist isort-example.plot
#
# Notice the "-persist" option, which keeps the figure window open
# after gnuplot exits.
#

set key left
set title 'insertion sort on random data'
set ylabel 'time [ms]'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
plot 'isort-example.data' u 1:7 w lp t 'min', 'isort-example.data' u 1:8 w lp t 'avg', 'isort-example.data' u 1:9 w lp t 'max'
