set terminal qt
set title "Average Land Temperatures"
set xlabel "Years after Beginning of Century"
set ylabel "Temperature (Celsius)"
set yrange [6.5:10]
set key top right
plot "Question-7-1800.dat" title "19th Century" linetype 7 linecolor 1 with linespoints, \
     "Question-7-1900.dat" title "20th Century" linetype 7 linecolor 2 with linespoints