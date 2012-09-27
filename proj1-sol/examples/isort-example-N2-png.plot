#
# isort-example-N2-png.plot
#
# Produces a PNG image file to be included in a report. Otherwise it
# is identical to isort-example-N2.plot. The output image file will be
# called isort-example-N2.png.
#
# Run this script from the command line, like this:
#
#   gnuplot isort-example-N2-png.plot
#

O(N) = N * N
set key right
set title 'insertion sort on random data, convergence for O(N^2)'
set ylabel 'time [ms] / (N^2)'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
set yrange [0:2e-6]
set term png
set output 'isort-example-N2.png'
plot 'isort-example.data' u 1:($7/O($1)) w lp t 'min', 'isort-example.data' u 1:($8/O($1)) w lp t 'avg', 'isort-example.data' u 1:($9/O($1)) w lp t 'max'
