set terminal png
set output 'Yearly Temperatures.png'
set title " Yearly Temperatures"
set xlabel "Years"
set ylabel "Temperatures"
set yrange [0: 10]
set key box
set key bottom right
set key width 5
set key width 4
plot "Question-6.dat" title "Yearly Temperatures" linetype 7 linecolor 2 with linespoints
