set title "Temperature minimum, maximum et moyenne par station"
set border 4095 from lt block linewidth 1.000 dashtype solid
set datafile separator ";"
set xlabel "Identifiant de la station"
set ylabel "Temperature (en °C)"
set xtics rotate by 90
plot "filtered" using 0:3:4:xticlabels(1) with filledcurve title "T Min et T Max", \
  '' using 0:2:xticlabels(1) smooth acspline lw 2 title "T moyenne"
