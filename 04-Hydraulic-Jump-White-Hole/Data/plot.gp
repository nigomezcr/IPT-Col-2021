nameCSV = filename.'.csv'
nameLOG = filename.'.log'

f(x) = a*x + b

set fit logfile nameLOG
set fit quiet

fit f(x) nameCSV u 1:2:3:4 xyerrors via a,b

set terminal pdfcairo enhanced font "Great Vibes"
set output filename.'.pdf'

set ylabel "{/Symbol F} (L/min)"
set xlabel "R (cm)"

set title filename

valuea = sprintf("%1.3f", a)
valueb = sprintf("%1.3f", b)
chisquare = sprintf("%1.2e", FIT_WSSR)
name = "f(x) = ".valuea."*x + ".valueb."&{8} {/Symbol c}^2 = ".chisquare
set key top center title name

plot nameCSV u 1:2:3:4 with xyerrorbars notitle, f(x) notitle


#print(filename.'\t'.value)




