nameCSV = filename.'.csv'
nameLOG = filename.'.log'

f(x) = a*x + b

set fit logfile nameLOG
set fit quiet

fit f(x) nameCSV u (log($1)):(log($2)) via a,b

print(abs(a))
