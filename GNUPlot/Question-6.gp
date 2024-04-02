reset
set terminal qt size 640,480
set title "Yearly Temperatures from 1760 to 2015"
set xtics nomirror
set ytics nomirror
set xlabel "Year"
set ylabel "Temperature (C)"
set xrange [1750:2025]
set yrange [2:11]
set key top right
plot "Question-6.dat" title "Yearly Temperatures" linetype 7 linecolor 2 with linespoints
