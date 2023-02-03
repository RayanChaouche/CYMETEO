(abscisse = jour, ordonne = valeurs)
(1 ligne = 1 station)
(si pour mm heure, mm couleur)

set datafile separator ";"
set timefmt "%Y-%m-%dT%H:%M:%S%z"
set xdata time
set format x "%Y-%m-%d\n%H:%M:%S"
set xtics rotate by 90
set style data linespoints
plot "sortie.txt" using 1:3 with linespoints linetype 7 lc 7









set timefmt "%Y-%m-%dT%H:%M:%S%z"

set xdata time

set format x "%Y-%m-%d\n%H:%M:%S"

set xtics rotate by 90

set style data linespoints

colors = "red blue green yellow purple"

hour_counter = 1

do for[i=0:*]{
	plot "sortie.txt" using 1:3 with linespoints linetype (hour_counter % 6) + 1 lc rgb word(colors, (hour_counter % 6) + 1) title strftime("%H:%M:%S", timecolumn(2))
	hour_counter = hour_counter + 1
}








set terminal png
set output "graph.png"
set xdata time
set timefmt "%Y-%m-%dT%H:%M:%S%z"
set format x "%m-%d"
set xtics rotate by -45
set ytics
set grid
set key autotitle columnheader

plot "sortie.txt" using 2:3 with lines lc rgb (int(strftime("%H", strptime(column(2), "%Y-%m-%dT%H:%M:%S%z")))%12==0 ? "red" : \
                                                 (int(strftime("%H", strptime(column(2), "%Y-%m-%dT%H:%M:%S%z")))%12==1 ? "green" : \
                                                 (int(strftime("%H", strptime(column(2), "%Y-%m-%dT%H:%M:%S%z")))%12==2 ? "blue" : "black" ))) notitle




















