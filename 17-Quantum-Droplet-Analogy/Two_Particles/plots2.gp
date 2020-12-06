set xrange [-20:20]
set yrange [-10:10]
set xlabel "x [mm]"
set ylabel "y [mm]"
set terminal pdf
set output "two_drops.pdf"
p 'data2.txt' u 2:3 t "Drop 1" w l lt 2, "" u 5:6 t "Drop 2" w l lt 4

set yrange [0:1]
set ylabel "z [mm]"
set output "z-x.pdf"
p 'data2.txt' u 2:4 t "Drop 1" w l lt 2, "" u 5:7 t "Drop 2" w l lt 4
