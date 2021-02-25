import numpy as np
import matplotlib.pyplot as plt


R = 1.65 #in cm 
M = 8.8e3 #in A/cm   
L = 1.   #in cm
MU0 = 4 * np.pi * 1e-5  # in T cm / A units


def Banal(z):
    return 0.5*M*MU0*(z/np.sqrt(z**2 + R**2) - (z-L)/np.sqrt((z-L)**2 + R**2))*10**6


Bexp = np.loadtxt("exp-magnetic-data.txt")
Bz_values = Bexp[:,1]


#    z_array = np.arange(L,15*L,0.1)
z_values = Bexp[:,0]
Baz = np.zeros(Bexp[:,0].size)
    
    

for i in range(Bexp[:,0].size):
    z = z_values[i]
    Baz[i]= Banal(z)
    #print(z, B(0,z))

plt.xlabel('z [cm]')
plt.ylabel('$B [\mu T]$')
plt.plot(z_values, Baz, 'gray')
#plt.plot(z_values, Bz_values, 'green', linestyle='dotted')



