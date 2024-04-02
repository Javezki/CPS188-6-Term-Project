set terminal qt
set title "Yearly Temperatures fom 1760 to 2015"
set xlabel "Year"
set ylabel "Temperature (C)"
set xrange [1750:2025]
set yrange [2:11]
set key top right
plot "Question-6.dat" title "Yearly Temperatures" linetype 7 linecolor 2 with linespoints