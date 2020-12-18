#!/bin/bash

map=false
vector2d=false
vector3d=false
run=false
scatter=false

while getopts f:o:mvVrs flag # the ':' after each flag means it requires an argument
    do
        case "${flag}" in
            f) file_to_plot=${OPTARG};;
            o) output_file=${OPTARG};;
            m) map=true ;;
            v) vector2d=true ;;
            V) vector3d=true ;;
            r) run=true ;;
            s) scatter=true ;;
        esac
    done

if [ "$map" = true ]; then
    rm plot.gnu
    echo "set pm3d map" >> "plot.gnu"
    echo "set size ratio 1" >> "plot.gnu"
    echo "set term png" >> "plot.gnu"
    echo "set output '$output_file'" >> "plot.gnu"
    echo "splot '$file_to_plot'" >> "plot.gnu"
    echo "gnuplot file built"
fi

if [ "$vector2d" = true ]; then
    rm plot.gnu
    echo "set term png" >> "plot.gnu"
    echo "set output '$output_file'" >> "plot.gnu"
    echo "plot '$file_to_plot' w vec" >> "plot.gnu"
    echo "gnuplot file built"
fi

if [ "$scatter" = true ]; then
    rm plot.gnu
    echo "set term png" >> "plot.gnu"
    echo "set output '$output_file'" >> "plot.gnu"
    echo "plot '$file_to_plot'" >> "plot.gnu"
    echo "gnuplot file built"
fi

# With time I'll add the other options...

if [ "$run" = true ]; then
    echo "running..."
    gnuplot plot.gnu
    rm plot.gnu
fi
