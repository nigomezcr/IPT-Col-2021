dir="Images/"

for i in $dir*; do
    ./x.read_image $i
    gnuplot -e "filename='Data_FD/"${i:7:-4}"'" plot.gp > data.csv
<<<<<<< HEAD
<<<<<<< HEAD
done
=======
done 
>>>>>>> 17edb1446fca68067aecc0b1d77634a9de120534
=======
done
>>>>>>> 9153b184492d84e8457959d3c31110d75103785d
