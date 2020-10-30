set terminal pdf
set output "x-t.pdf"
set xlabel "t"
set ylabel "x"
p 'data.txt' u 1:2 t "x-t" w l lt 1
set ylabel "y"
set output "y-t.pdf"
p 'data.txt' u 1:3 t "y-t" w l lt 2
set ylabel "z"
set output "z-t.pdf"
p 'data.txt' u 1:4 t "z-t" w l lt 3
set output "y-x.pdf"
set xlabel "x"
set ylabel "y"
p 'data.txt' u 2:3 t "y-x" w l lt 4
set output "y-z.pdf"
p 'data.txt' u 4:3 t "y-z" w l lt 5
