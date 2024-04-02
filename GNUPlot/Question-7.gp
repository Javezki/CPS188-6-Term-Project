reset
set terminal qt size 640,480
set title "Average Land Temperatures For 19th and 20th Centuries"
set xtics nomirror
set ytics nomirror
set xlabel "Year Relative to Beginning of Century"
set ylabel "Temperature (C)"
set yrange [6.5:10]
set xrange [-5:105]
set key top right
plot "Question-7-1800.dat" title "19th Century" linetype 7 linecolor 1 with linespoints, \
     "Question-7-1900.dat" title "20th Century" linetype 7 linecolor 2 with linespoints
