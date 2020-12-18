nameCSV = filename.'.csv'

set terminal pdfcairo enhanced font "Z003,16"
set output filename.'.pdf'

set xlabel "{/Symbol F} (ml/s)"
set ylabel "R (mm)"

#set title "Expanded polystyrene"

f(x) = 3.42235*x**(0.75)

conv1 = 100./6.
conv2 = 1e1

plot nameCSV u ($2*conv1):($1*conv2):($4*conv1):($3*conv2) with xyerrorbars notitle, f(x) notitle


#print(filename.'\t'.value)




