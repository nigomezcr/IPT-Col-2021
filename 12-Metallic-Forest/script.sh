dir="Images/"

for i in $dir*; do
    ./x.read_image $i
    gnuplot -e "filename='Data_FD/"${i:7:-4}"'" plot.gp > data.csv
<<<<<<< HEAD
done
=======
done 
>>>>>>> 17edb1446fca68067aecc0b1d77634a9de120534
