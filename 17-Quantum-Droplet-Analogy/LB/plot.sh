#!/bin/bash

# Gnuplot script generator

# Arguments:
#     f: file to plot
#     o: output file name

#     s: scatter plor
#     m: 2D heat map
#     v: 2D vector plot
#     V: 3D vector plot
#     M: 2D heat map & vector plot

#     r: don't run the gnuplot script

# Usage:
#     bash plot.sh -f file_to_plot.csv -o output_file.png [flags]

# Author: Juan Vanegas. Git: jpvanegasc



map=false
vector2d=false
vector3d=false
run=true
scatter=false
scatter3d=false
heat_vector=false

while getopts f:o:mMvVsSr flag # the ':' after each flag means it requires an argument
    do
        case "${flag}" in
            f) file_to_plot=${OPTARG};;
            o) output_file=${OPTARG};;
            m) map=true ;;
            v) vector2d=true ;;
            V) vector3d=true ;;
            r) run=false ;;
            s) scatter=true ;;
            S) scatter3d=true ;;
            M) heat_vector=true ;;
        esac
    done

if [ "$map" = true ]; then
    rm plot.gnu
    echo "set datafile separator ','" >> "plot.gnu"
    echo "set pm3d map" >> "plot.gnu"
    echo "set size ratio 1" >> "plot.gnu"
    echo "set term png" >> "plot.gnu"
    echo "set output '$output_file'" >> "plot.gnu"
    echo "splot '$file_to_plot'" >> "plot.gnu"
    echo "gnuplot file built"
fi

if [ "$vector2d" = true ]; then
    rm plot.gnu
    echo "set datafile separator ','" >> "plot.gnu"
    echo "set term png" >> "plot.gnu"
    echo "set output '$output_file'" >> "plot.gnu"
    echo "plot '$file_to_plot' w vec" >> "plot.gnu"
    echo "gnuplot file built"
fi

if [ "$scatter" = true ]; then
    rm plot.gnu
    echo "set datafile separator ','" >> "plot.gnu"
    echo "set term png" >> "plot.gnu"
    echo "set output '$output_file'" >> "plot.gnu"
    echo "plot '$file_to_plot'" >> "plot.gnu"
    echo "gnuplot file built"
fi

if [ "$scatter3d" = true ]; then
    rm plot.gnu
    echo "set datafile separator ','" >> "plot.gnu"
    echo "set term png" >> "plot.gnu"
    echo "set output '$output_file'" >> "plot.gnu"
    echo "splot '$file_to_plot'" >> "plot.gnu"
    echo "gnuplot file built"
fi

if [ "$heat_vector" = true ]; then
    rm plot.gnu
    echo "set datafile separator ','" >> "plot.gnu"
    echo "set pm3d map" >> "plot.gnu"
    echo "set size ratio 1" >> "plot.gnu"
    echo "set term png" >> "plot.gnu"
    echo "set output '$output_file'" >> "plot.gnu"
    echo "splot '$file_to_plot' using 1:2:5 notitle, '' using 1:2:(0):3:4:(0) notitle w vec linecolor rgb '#000000'" >> "plot.gnu"
    echo "gnuplot file built"
fi

# With time I'll add the other options...

if [ "$run" = true ]; then
    echo "running..."
    gnuplot plot.gnu
    rm plot.gnu
fi
