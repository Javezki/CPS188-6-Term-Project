set terminal png

set output "question-7.png"

set title "Century Temperatures"

set xlabel "Year"

set ylabel "Average Temperatures"

plot "yearlyAverages.dat"