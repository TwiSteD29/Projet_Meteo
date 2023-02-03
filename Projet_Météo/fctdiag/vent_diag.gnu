set datafile separator ";"
set title "Carte des vents"
set border 4095 from lt block linewidth 1.000 dashtype solid
set xlabel "Longitude"
set ylabel "Latitude"
set xrange [-180.00 : 180.00 ]
set yrange [ -90.00 : 90.00 ]
plot "filtered" using 5:4:3:2 with vectors


