#!/usr/bin/env python3
# -*- coding":"utf-8 -*-
import numpy as np

# Constants
Lx = 129103
Ly = 1024

Lx_2 = int(Lx/2)
Ly_2 = int(Ly/2)

lamb = 532.0
k0 = 2.0*np.pi/lamb

n_bar = 1.003
V0 = (k0**2)*((n_bar**2) - (1.33**2))

one_pi = 1.0/np.pi

# progress
def print_progress(x):
    progress = int(x*100/Lx)
    progress_str = '#'*progress + ' '*(100-progress)
    print(f"0% [{progress_str}] 100%", end='\r', flush=True)

def arctan_smooth(x, y, funct, delay=1000):
    return one_pi*np.arctan( (x-funct(y))/delay )+0.5

# Potential 0
def potential0():
    file = open("V_0.csv", 'w+')

    for x in range(Lx):
        line = ""
        for y in range(Ly-1):
            v = 0.0

            line += f"{v},"

        v = 0.0
        line += f"{v}\n"
        file.write(line)

        print_progress(x)

    done = '#'*100
    print(f"0% [{done}] 100%")
    file.close()

# Angled glass
def angle(y, d=Lx/10):
    return 2.0*d*y/Ly + Lx_2 - d

def glass():
    n_bar = 1.003
    file = open("V_angled.csv", 'w+')

    for x in range(Lx):
        line = ""
        for y in range(Ly-1):
            v = V0*arctan_smooth(x, y, angle)

            line += f"{v},"

        v = V0*arctan_smooth(x, Ly-1, angle)
        line += f"{v}\n"
        file.write(line)

        print_progress(x)

    done = '#'*100
    print(f"0% [{done}] 100%")
    file.close()

# Convex Lens
def convex_lens(y, d=Lx/10):
    return 2*d*(y-Ly_2)**2/(Ly*Ly) + Lx_2 - d

constant = lambda x: Lx_2

def convex():
    n_bar = 1.003
    file = open("V_convex.csv", 'w+')

    for x in range(Lx):
        line = ""
        for y in range(Ly-1):
            v = V0*(arctan_smooth(x, y, convex_lens) - arctan_smooth(x,y,constant))

            line += f"{v},"

        v = V0*(arctan_smooth(x, Ly-1, convex_lens) - arctan_smooth(x,Ly-1,constant))
        line += f"{v}\n"
        file.write(line)

        print_progress(x)

    done = '#'*100
    print(f"0% [{done}] 100%")
    file.close()

# Periodic
def periodic(v_period):
    """
    v_period is the potential period on both axis
    """
    file = open(f"V_periodic_L{int(v_period)}.csv", 'w+')

    factor = 2.0*np.pi/v_period

    for x in range(Lx):
        line = ""
        sin_x = np.sin(factor*x)

        for y in range(Ly-1):
            v = V0*0.5*(sin_x + np.sin(factor*y))

            line += f"{v},"

        v = V0*0.5*(sin_x + np.sin(factor*(Ly-1)) )
        line += f"{v}\n"
        file.write(line)

        print_progress(x)

    done = '#'*100
    print(f"0% [{done}] 100%")
    file.close()

if __name__ == "__main__":
    # potential0()
    # glass()
    # convex()

    periods = [10, 100, 200, 300, 400, 500, 600, 700, 800, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]

    for period in periods:
        periodic(period)
