set terminal png
set output 'Question-10.png'
set title " Montly Tempeatures"
set xlabel "Months"
set ylabel "Temperatures"
set yrange [0: 20]
set key box
set key bottom right
set key width 5
set key width 4
plot 'Question-10.dat' title "Error Bars" linecolor 8 with yerrorbars,\
    'Question-10.dat' title "Temperatures" linecolor 3 with lines