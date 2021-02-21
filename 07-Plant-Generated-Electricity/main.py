#Libraries
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from os import listdir



#Average voltage
def get_averages(folder:str)->list:
    """
    Input
    ============
    Output
    ============
    """
    Files = [file for file in listdir("Data/"+folder) if file[-4:]==".csv"]

    Voltages = []
    for file in Files:
        data = pd.read_csv("Data/"+folder+"/"+file)
        voltage = data["Voltage"].to_numpy()
        Voltages.append(voltage)

    Voltages = np.array(Voltages)

    Averages = []
    for proto in Voltages:
        averages = []
        for ii in range(0, len(proto)-1,5):
            averages.append(round(sum(proto[ii:ii+5])/5.,2))
        Averages.append(averages)

    Averages = np.array(Averages)
    finalAverages = [round(jj,2) for jj in np.sum(Averages, axis = 0)/5.]
    finalAverages.pop(0)

    return finalAverages

#print(get_averages("Dead-Soil"))

#Plots
def get_plots(**kwargs)->plt.figure:
    """

    Input
    ============
    Output
    ============
    """
    final = plt.figure()
    labels = list(kwargs.keys())
    count = 0
    for arg in kwargs.values():
        plt.plot(arg, label= labels[count])
        count += 1
    plt.xlabel(r"Time")
    plt.ylabel(r"Volage (V)")
    plt.legend()
    plt.grid(True, linestyle="--", linewidth=0.2)
    plt.show()

    return final

get_plots(Dead_Soil = get_averages("Dead-Soil"),
            Living_Soil = get_averages("Living-Soil"),
            Plants_Light = get_averages("Plants-Light"),
            Plants_No_Light = get_averages("Plants-No-Light"))
