set terminal png
set output 'Yearly Land and Ocean Averages.png'
set title "Yearly Land and Ocean Averages"
set xlabel "Year"
set ylabel "Temperatures"
set yrange [0: 20]
set key box
set key top right
set key width 5
set key width 4
plot "Question-11-Land.dat" title "Land Yearly Average Temperature" linetype 7 linecolor 1 with linespoints, \
     "Question-11-Land and Ocean.dat" title "Land and Ocean Yearly Average Temperature" linetype 7 linecolor 2 with linespoints