set xrange [-1:1]
set yrange [-0.01:0.01]
set xlabel "x [m]"
set ylabel "y [m]"
set terminal pdf
set output "two_drops.pdf"
p 'data2.txt' u 2:3 t "Drop 1" w l lt 2, "" u 5:6 t "Drop 2" w l lt 4
