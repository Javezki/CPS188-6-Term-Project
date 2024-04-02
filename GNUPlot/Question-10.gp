reset
set terminal qt size 640,480
set title "Monthly Temperatures Between 2000-2015"
set xtics nomirror
set ytics nomirror
set xlabel "Month"
set ylabel "Temperature (C)"
set yrange [2:17.5]
set xrange [-5:197]
set xtics 12
set key top right
plot "Question-10.dat" using 1:2:3 with errorbars title "Error Bars", \
    "Question-10.dat" using 1:2 with lines title "Monthly Temperature"
