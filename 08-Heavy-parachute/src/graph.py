import numpy as np
import matplotlib.pyplot as plt

R = 1
M = 1
L = 1
MU0 = 4 * np.pi * 1e-5  # in T cm / A units


z_values = np.linspace(0, 10, 51)
r_values = np.array([0] + [0.5 * (1.2**i) for i in range(18)])

Bz = np.loadtxt("magnetic-data.txt")


def analytic(z):
    a = z/np.sqrt(z**2 + R**2)
    b = (z-L)/np.sqrt((z-L)**2 + R**2)

    return 0.5*MU0*M * (a-b)


plt.plot(z_values, Bz[:, 0])
plt.plot(z_values, analytic(z_values))
plt.show()
