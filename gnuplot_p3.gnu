#!/usr/local/bin/gnuplot -persist
set datafile separator ";"
set xrange [-50:140]
set yrange[-70:60]
unset key
set term pngcairo
set term pngcairo size 1280, 960
set output "graphique.png"


plot for [i=0:*] "sortie.txt" every ::i::i using 2:3 with lines



