#Libraries
import plotly
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from os import listdir

#Reading measurements->Average voltage
def get_averages(folder:str)->list:
    """
    This function takes data, precisely voltage, from a given folder (named after
    a group of prototypes associated to an experiment) which contains csv files
    associated to the respective prototypes. As return we have a list with
    the averages voltages for the whole group.

    Input
    ============
    folder (str): name of the folder from which data is taken.

    Output
    ============
    finalAverages (list): list with the average voltage for a complete set of
                          measurements, i.e. morning or night.
    """
    Files = [file for file in listdir("Data/"+folder) if file[-4:]==".csv"]

    #Reading data from csv files
    Voltages = []
    for file in Files:
        data = pd.read_csv("Data/"+folder+"/"+file)
        voltage = data["Voltage"].to_numpy()
        Voltages.append(voltage)

    #order
    Voltages = np.array(Voltages)
    Voltages = Voltages.reshape(len(Voltages),int(len(Voltages[0])/5.), 5)
    #Taking averages for each set of measurements for each prototype
    averageProto = np.sum(Voltages, axis = 2)/5.
    averageProto = np.transpose(np.array(averageProto))
    #Taking averages for the whole group

    #finalAverages = [round(jj,2) for jj in np.sum(averageProto, axis =1)/5.]
    #finalAverages = finalAverages[2:] #Delete first measurements, not reliable

    #return averageProto
    return averageProto

#print(get_averages("Living-Soil")) #testing


#Statistics
pd.options.plotting.backend = "plotly" #Necessary for boxplots (?)

def get_boxPlot(avProto:np.array):
    """
    MISSING UNCERTAINTIES AND RELATED STATISTICS
        -> Show in our plots the whole ensemble statistics (Box plots + whyskers?)
        -> How to use what we have, if possible, to support our results?
           Specifically answer wheter photosynthesis is indeed involved by
           comparing Plants_Light with Plants_No_Light.
        -> Quantize the effect of humidity for each experiment.
    """
    #avProto = np.array(avProto)
    #df = pd.DataFrame(avProto)
    boxes = plt.figure()
    boxData = [x for x in avProto]
    plt.boxplot(boxData)
    plt.show()
    #print(df)
    return boxes

get_boxPlot(get_averages("Plants-Light"))
#get_boxPlot(get_averages("Plants-No-Light"))



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
    plt.grid(True, linestyle="--", linewidth=0.3)
    plt.show()

    return final

"""
get_plots(Dead_Soil = get_averages("Dead-Soil"),
            Living_Soil = get_averages("Living-Soil"),
            Plants_Light = get_averages("Plants-Light"),
            Plants_No_Light = get_averages("Plants-No-Light"))
"""
