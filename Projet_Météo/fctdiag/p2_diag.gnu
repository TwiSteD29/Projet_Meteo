set datafile separator ";"
set title "Moyenne Pression selon la date"
set border 4095 from lt block linewidth 1.000 dashtype solid
set xlabel "Date"
set ylabel "Pression Moyenne"
plot "filtered" using 1:2 with linespoint title ""
