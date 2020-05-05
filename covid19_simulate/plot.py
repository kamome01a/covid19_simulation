import numpy as np
import matplotlib.pyplot as plt
import sys

def read(Name='a.dat'):
    x=np.loadtxt(Name,delimiter=' ',usecols=0)
    y=np.loadtxt(Name,delimiter=' ',usecols=1)

    return(x,y)

args=sys.argv
for i in range(int(int(args[1])*24*60/15.)):
    x_infection,y_infection=read("./output/Infection%d.dat"%(i))
    x_helth,y_helth=read("./output/Not_infection%d.dat"%(i))
    x_recover,y_recover=read("./output/Recovery%d.dat"%(i))
    plt.figure(figsize=(10,10))
    plt.scatter(x_infection,y_infection,color="red",label="Infection")
    plt.scatter(x_helth,y_helth,color="green",label="helth")
    plt.scatter(x_recover,y_recover,color="blue",label="recovery")
    plt.savefig("./png/step%08.f.png"%(i))

    
