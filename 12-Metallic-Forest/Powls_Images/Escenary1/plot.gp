nameCSV = 'Data_FD_processed/'.filename.'.csv'
nameLOG = 'Data_FD_processed/'.filename.'.log'

f(x) = a*x + b

set fit logfile nameLOG
set fit quiet

fit f(x) nameCSV u (log($1)):(log($2)) via a,b

set terminal pdfcairo enhanced font "Mf Young & Beautiful"
set output 'Data_FD_processed/'.filename.'.pdf'

set xlabel "log({/Symbol e})"
set ylabel "log(N)"

set title filename

value = sprintf("%1.3f", abs(a))
chisquare = sprintf("%1.2e", FIT_WSSR)
name = "dim_H = ".value."&{8} {/Symbol c}^2 = ".chisquare
set key top center title name

plot nameCSV u (log($1)):(log($2)) notitle, f(x) notitle

print(filename.'   '.value)




