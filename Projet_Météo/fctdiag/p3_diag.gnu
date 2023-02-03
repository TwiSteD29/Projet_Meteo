set datafile separator ";"
set title "Pression moyenne par jour selon la station"
set border 4095 from lt block linewidth 1.000 dashtype solid
set xlabel "Date"
set ylabel "Pression moyenne"
set palette color positive
plot "filtered2" using 1:3:2 with linespoint palette title ""
