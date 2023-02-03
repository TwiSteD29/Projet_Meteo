set title "Pression minimum, maximum et moyenne par station"
set datafile separator ";"
set border 4095 from lt block linewidth 1.000 dashtype solid
set xlabel "Identifiant de la station"
set ylabel "Pression"
set xtics rotate by 45 right
plot "filtered" using 0:3:4:xticlabels(1) with filledcurve title "P Min et P Max", \
  '' using 0:2:xticlabels(1) smooth acspline lw 2 title "P moyenne"
  
