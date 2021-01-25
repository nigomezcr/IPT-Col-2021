import numpy as np
import matplotlib.pyplot as plt
from scipy import optimize
import seaborn as sns
import pandas as pd

escen1 = np.genfromtxt('Escenary1/data.csv', delimiter="\t")
#escen2 = np.genfromtxt('Escenary2/data.csv', delimiter="\t")
#escen3 = np.genfromtxt('Escenary3/data.csv', delimiter="\t")
escen4 = np.genfromtxt('Escenary4/data.csv', delimiter="\t")
escen5 = np.genfromtxt('Escenary5/data.csv', delimiter="\t")

df = pd.DataFrame({'2 gramos': escen4, '5 gramos': escen1,'8 gramos': escen5})#, 'Escenary4': escen4, 'Escenary5': escen5})
plt.figure(figsize=(4,6))
sns.violinplot(data=df,orient="v",width= 1.0,linewidth=0.7,constrained_layout=False)
#plt.yscale('log')
#plt.ylim(1e-3,100)
#plt.hlines(10.3169, -0.5, 3.5, 'k', 'dashed')
plt.ylabel("Dimensión fractal")
plt.xlabel("Escenarios")
plt.title("Distinta masa de la sal")
plt.tight_layout()
plt.show()
