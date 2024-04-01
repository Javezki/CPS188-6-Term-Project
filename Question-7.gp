set terminal png
set output 'Average Land Temperatures.png'
set title "Average Land Temperatures"
set xlabel "Years in the 18th and 19th centuries"
set ylabel "Temperatures"
set yrange [0: 10]
set key box
set key bottom right
set key width 5
set key width 4
plot "Question-7-1800.dat" title "Average Land Temperatures 19th century" linetype 7 linecolor 1 with linespoints, \
     "Question-7-1900.dat" title "Average Land Temperatures 20th century" linetype 7 linecolor 2 with linespoints