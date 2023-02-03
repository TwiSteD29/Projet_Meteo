set pm3d implicit at b
set border 4095 front lt black linewidth 1.000 dashtype solid
set title "Altitude selon la Station"
set xlabel "Longitude"
set ylabel "Latitude"
set cblabel "Altitude"
set datafile separator ";"
set view map
set pm3d interpolate 0,0
set hidden3d
set dgrid3d 200,200
set palette color positive
stats "filtered" using 3:2
splot [STATS_min_x:STATS_max_x] [STATS_min_y:STATS_max_y] "filtered" using 3:2:1 with lines title ""



