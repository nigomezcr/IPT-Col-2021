import numpy as np
import matplotlib.pyplot as plt

R = 1
M = 1
L = 1
MU0 = 4 * np.pi * 1e-5  # in T cm / A units


def f(r_prim, z_prim, r, z):

    norm = np.sqrt((r - r_prim)**2 + (z - z_prim)**2)

    a = 3 * (z - z_prim)**2
    a = a / (norm**5)

    b = 1 / (norm**3)

    return (0.5 * M * MU0 * r_prim) * (a - b)


def int2d(func, x_min, x_max, h, y_min, y_max, k, *args):

    def ff(x, y): return func(x, y, *args)

    x_num = int((x_max - x_min) / h)
    y_num = int((y_max - y_min) / k)

    x = np.linspace(x_min, x_max, x_num)
    y = np.linspace(y_min, y_max, y_num)

    integral = 0
    for i in x:
        for j in y:
            A = ff(i-h, j-k) + ff(i+h, j-k) + \
                ff(i-h, j+k) + ff(i+h, j+k)

            B = ff(i, j-k) + ff(i, j+k) + ff(i-h, j) + ff(i+h, j)

            C = ff(i, j)

            integral += A + 4*B + 16*C

    return k*h*integral / 9


z_values = np.linspace(0, 10, 51)
r_values = np.array([0] + [0.5 * (1.2**i) for i in range(18)])

table = []

for z in z_values:
    row = []
    for r in r_values:
        row.append(int2d(f, 0, R, 0.01, 0, L, 0.01, r, z))

    table.append(row)

table = np.array(table)


np.savetxt("magnetic-data.txt", table)
