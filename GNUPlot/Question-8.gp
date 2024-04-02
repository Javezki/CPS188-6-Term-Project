set terminal qt
set title "Yearly Land Temperatures Between 1850-2015"
set xlabel "Year"
set ylabel "Temperature (C)"
set yrange [0:20]
set key top right
plot "Question-8-lat.dat" title "Average Temperature" with l dt 1 lw 4 linecolor 'purple', \
     "Question-8-lmt.dat" title "Average Max Temperature" with l, \
     "Question-8-lmit.dat" title "Average Min Temperature" with l