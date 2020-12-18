dir="processed/"

for i in $dir*; do
    #../../x.read_image $i
    gnuplot -e "filename='${i:10:-4}'" plot.gp
done
