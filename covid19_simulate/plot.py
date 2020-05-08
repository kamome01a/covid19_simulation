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

step=np.loadtxt("rate.dat",delimiter=' ',usecols=0,dtype="int")
infection=np.loadtxt("rate.dat",delimiter=' ',usecols=1)
helth=np.loadtxt("rate.dat",delimiter=' ',usecols=2)
recover=np.loadtxt("rate.dat",delimiter=' ',usecols=3)
die=np.loadtxt("rate.dat",delimiter=' ',usecols=4)
zero=np.zeros(np.max(step)-1)

plt.figure()
plt.plot(step,helth,color="green")
plt.plot(step,infection,color="red")
plt.plot(step,recover,color="blue")
plt.plot(step,die,color="black")

plt.fill_between(step,infection,color="red",alpha=0.5)
plt.fill_between(step,infection,helth,where=helth>infection,color="green",alpha=0.5)
plt.fill_between(step,helth,recover,where=recover>helth,color="blue",alpha=0.5)
plt.fill_between(step,recover,die,where=die>recover,color="black",alpha=0.5)

plt.savefig("rate_stop_release_step_by_step.png")
