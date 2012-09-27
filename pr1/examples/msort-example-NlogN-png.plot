#
# msort-example-NlogN-png.plot
#
# Produces a PNG image file to be included in a report. Otherwise it
# is identical to msort-example-NlogN.plot. The output image file will
# be called msort-example-NlogN.png.
#
# Run this script from the command line, like this:
#
#   gnuplot msort-example-NlogN-png.plot
#

O(N) = N * log(N)
set key left
set title 'merge sort on random data, convergence for O(N log N)'
set ylabel 'time [ms] / (N log N)'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
set term png
set output 'msort-example-NlogN.png'
plot 'msort-example.data' u 1:($7/O($1)) w lp t 'min', 'msort-example.data' u 1:($8/O($1)) w lp t 'avg', 'msort-example.data' u 1:($9/O($1)) w lp t 'max'
