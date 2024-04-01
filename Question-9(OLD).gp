set multiplot layout 2,2 title 'Average, Max, and Min Temperatures Over Four Centuries'
set ylabel 'Temperature (Celsius)'
set xlabel 'Metric'
set style data histograms
set style fill pattern 5
plot 'Question-9-firstCentury.dat' using 2:xtic(1) linecolor 'red' title '17th Century'
plot 'Question-9-secondCentury.dat' using 2:xtic(1) linecolor 'blue' title '18th Century'
plot 'Question-9-thirdCentury.dat' using 2:xtic(1) linecolor 'green' title '19th Century'
plot 'Question-9-fourthCentury.dat' using 2:xtic(1) linecolor 'purple' title '20th Century'
