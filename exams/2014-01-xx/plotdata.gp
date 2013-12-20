set term pdf
set format ""
set yrange [0:*]



set output 'flin1.pdf'
plot 'data3' u 1:2 w lp t ''

set output 'flin1-log.pdf'
plot 'data3' u 1:($2/log($1)) w lp t ''

set output 'flin1-n.pdf'
plot 'data3' u 1:($2/$1) w lp t ''

set output 'flin1-n2.pdf'
plot 'data3' u 1:($2/$1/$1) w lp t ''



set output 'flog1.pdf'
plot 'data3' u 1:3 w lp t ''

set output 'flog1-log.pdf'
plot 'data3' u 1:($3/log($1)) w lp t ''

set output 'flog1-n.pdf'
plot 'data3' u 1:($3/$1) w lp t ''

set output 'flog1-n2.pdf'
plot 'data3' u 1:($3/$1/$1) w lp t ''



set output 'fconst.pdf'
plot 'data3' u 1:4 w lp t ''

set output 'fconst-log.pdf'
plot 'data3' u 1:($4/log($1)) w lp t ''

set output 'fconst-n.pdf'
plot 'data3' u 1:($4/$1) w lp t ''

set output 'fconst-n2.pdf'
plot 'data3' u 1:($4/$1/$1) w lp t ''



set output 'flog2.pdf'
plot 'data3' u 1:5 w lp t ''

set output 'flog2-log.pdf'
plot 'data3' u 1:($5/log($1)) w lp t ''

set output 'flog2-n.pdf'
plot 'data3' u 1:($5/$1) w lp t ''

set output 'flog2-n2.pdf'
plot 'data3' u 1:($5/$1/$1) w lp t ''



set output 'fn2.pdf'
plot 'data3' u 1:6 w lp t ''

set output 'fn2-log.pdf'
plot 'data3' u 1:($6/log($1)) w lp t ''

set output 'fn2-n.pdf'
plot 'data3' u 1:($6/$1) w lp t ''

set output 'fn2-n2.pdf'
plot 'data3' u 1:($6/$1/$1) w lp t ''



set output 'flin2.pdf'
plot 'data3' u 1:7 w lp t ''

set output 'flin2-log.pdf'
plot 'data3' u 1:($7/log($1)) w lp t ''

set output 'flin2-n.pdf'
plot 'data3' u 1:($7/$1) w lp t ''

set output 'flin2-n2.pdf'
plot 'data3' u 1:($7/$1/$1) w lp t ''
