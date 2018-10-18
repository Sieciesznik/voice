import matplotlib
import matplotlib.pyplot as plt
import numpy as np


with open('..\\voice\\voice\\sample.txt','r') as sampleFile:
	a = [int(x) for x in sampleFile.read().split()]
	

fig, ax = plt.subplots()
ax.plot(a)


fig.savefig("plot.png")
plt.show()
	
	
input(' ')
