#!/usr/local/bin/gnuplot -persist
set datafile separator ";"
set cbrange [98:100]
set xrange [-50:140]
set yrange[-70:60]
set term pngcairo
set term pngcairo size 1280, 960
set output "graphique.png"
set table "sortie.txt"
i=1
while (i <= system("wc -l sortie.txt | awk '{print $1}'")) {
    angle = (column(2) * pi)/180 # Convert angle from degrees to radians
    set arrow i from (column(4) using (sprintf("sortie.txt", i))), (column(5) using (sprintf("sortie.txt", i))) to (column(4) + cos(angle) * column(3)) using (sprintf("sortie.txt", i)), (column(5) + sin(angle) * column(3))
    i = i + 1
}
plot x
