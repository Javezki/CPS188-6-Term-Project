reset
set terminal qt size 640,480
bm = 0.15
lm = 0.12
rm = 0.95
gap = 0.03
size = 0.75
y1 = 7.0; y2 = 10.4; y3 = 14.1; y4 = 16.5

set multiplot title "Yearly Land and Ocean Average Temperatures Between 1850-2015"
set xlabel 'Year'
set xrange [1840:2020]
set border 1+2+8
set xtics nomirror
set ytics nomirror
set lmargin at screen lm
set rmargin at screen rm
set bmargin at screen bm
set tmargin at screen bm + size * (abs(y2-y1) / (abs(y2-y1) + abs(y4-y3) ) )

set yrange [y1:y2]
plot "Question-11-Land.dat" title "Land Yearly Average Temperature" with lp lc 'green' pt 7

unset xtics
unset xlabel
set border 2+4+8
set bmargin at screen bm + size * (abs(y2-y1) / (abs(y2-y1) + abs(y4-y3) ) ) + gap
set tmargin at screen bm + size + gap
set yrange [y3:y4]

set label 'Temperature (C)' at screen 0.03, bm + 0.5 * (size + gap) offset 0,-strlen("Temperature (C)")/4.0 rotate by 90

set arrow from screen lm - gap / 4.0, bm + size * (abs(y2-y1) / (abs(y2-y1)+abs(y4-y3) ) ) - gap / 4.0 to screen \
lm + gap / 4.0, bm + size * (abs(y2-y1) / (abs(y2-y1) + abs(y4-y3) ) ) + gap / 4.0 nohead

set arrow from screen lm - gap / 4.0, bm + size * (abs(y2-y1) / (abs(y2-y1)+abs(y4-y3) ) ) - gap / 4.0  + gap to screen \
lm + gap / 4.0, bm + size * (abs(y2-y1) / (abs(y2-y1) + abs(y4-y3) ) ) + gap / 4.0 + gap nohead

set arrow from screen rm - gap / 4.0, bm + size * (abs(y2-y1) / (abs(y2-y1)+abs(y4-y3) ) ) - gap / 4.0 to screen \
rm + gap / 4.0, bm + size * (abs(y2-y1) / (abs(y2-y1) + abs(y4-y3) ) ) + gap / 4.0 nohead

set arrow from screen rm - gap / 4.0, bm + size * (abs(y2-y1) / (abs(y2-y1)+abs(y4-y3) ) ) - gap / 4.0  + gap to screen \
rm + gap / 4.0, bm + size * (abs(y2-y1) / (abs(y2-y1) + abs(y4-y3) ) ) + gap / 4.0 + gap nohead

plot "Question-11-Land and Ocean.dat" title "Land and Ocean Yearly Average Temperature" with lp lc 'blue' pt 7

unset multiplot
