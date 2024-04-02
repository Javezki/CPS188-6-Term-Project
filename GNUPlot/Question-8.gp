reset
set terminal qt size 640,480
set title "Yearly Land Temperatures Between 1850-2015"
set xtics nomirror
set ytics nomirror
set xlabel "Year"
set ylabel "Temperature (C)"
set yrange [0:19]
set key top right
plot "Question-8-lat.dat" title "Average Temperature" with l dt 1 lw 4 linecolor 'red', \
     "Question-8-lmt.dat" title "Average Max Temperature" with l, \
     "Question-8-lmit.dat" title "Average Min Temperature" with l
