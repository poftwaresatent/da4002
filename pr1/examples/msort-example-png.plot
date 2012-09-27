#
# msort-example-png.plot
#
# Produces a PNG image file to be included in a report. Otherwise it
# is identical to msort-example.plot. The output image file will be
# called msort-example.png.
#
# Run this script from the command line, like this:
#
#   gnuplot msort-example-png.plot
#

set key left
set title 'merge sort on random data'
set ylabel 'time [ms]'
set xlabel 'array length [N]'
set format x '%.1g'
set format y '%.2g'
set term png
set output 'msort-example.png'
plot 'msort-example.data' u 1:7 w lp t 'min', 'msort-example.data' u 1:8 w lp t 'avg', 'msort-example.data' u 1:9 w lp t 'max'
