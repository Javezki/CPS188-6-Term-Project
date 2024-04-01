set terminal qt enhanced size 800,1000
set multiplot layout 1,3 title 'Average, Max, and Min Temperatures per Century'
set ylabel 'Temperature (Celsius)'
set yrange [-7:24]
set ytics 1
set grid y
unset xtics
set style data histogram
set style histogram clustered gap 0
set boxwidth 1
set style fill pattern 1
set title 'Average'
plot 'Question-9.dat' every ::0::0 using 2 linestyle 7 title '19th Century', 'Question-9.dat' every ::1::1 using 2 linestyle 2 title '20th Century', 'Question-9.dat' every ::2::2 using 2 linestyle 4 title '21st Century'
set title 'Maximum'
plot 'Question-9.dat' every ::0::0 using 3 linestyle 7 title '19th Century', 'Question-9.dat' every ::1::1 using 3 linestyle 2 title '20th Century', 'Question-9.dat' every ::2::2 using 3 linestyle 4 title '21st Century'
set title 'Minimum'
plot 'Question-9.dat' every ::0::0 using 4 linestyle 7 title '19th Century', 'Question-9.dat' every ::1::1 using 4 linestyle 2 title '20th Century', 'Question-9.dat' every ::2::2 using 4 linestyle 4 title '21st Century'