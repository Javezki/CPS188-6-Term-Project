set terminal png
set output 'Question-8.png'
set title "Land Temperatures"
set xlabel "Year"
set ylabel "Temperatures"
set yrange [0: 20]
set key box
set key top right
set key width 5
set key width 4
plot "Question-8-lat.dat" title "Land Average Temperature" linetype 7 linecolor 1 with linespoints, \
     "Question-8-lmt.dat" title "Land Max Temperature" linetype 7 linecolor 2 with linespoints, \
     "Question-8-lmit.dat" title "Land Min Temperature" linetype 7 linecolor 3 with linespoints