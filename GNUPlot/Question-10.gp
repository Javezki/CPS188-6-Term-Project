set terminal qt
set title "Monthly Temperatures Between 2000-2015"
set xlabel "Months"
set ylabel "Temperature (C)"
set yrange [2:17]
set xrange [0:192]
set xtics 12
set key top right
plot "Question-10.dat" using 1:2:3 with errorbars title "Error Bars", \
    "Question-10.dat" using 1:2 with lines title "Monthly Temperature"