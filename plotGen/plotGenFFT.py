import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

'''
with open('..\\voice\\voice\\fft.txt','r') as sampleFile:
	try:
		array = [[ float(x) for x in line.split()] for line in sampleFile]
	except Exception as ex:
		print(ex)
		input(' ')

X = [math.sqrt(a[0] * a[0] + a[1] * a[1]) for a in array]

fig, ax = plt.subplots()
ax.plot(X[0:int((len(X)/2)+1)])
'''

with open('..\\voice\\voice\\fft.txt','r') as sampleFile:
	a = [math.sqrt(int(x)) for x in sampleFile.read().split()]
	

fig, ax = plt.subplots()
ax.plot(a)


print(len(a))

fig.savefig("plotfft.png")
plt.show()
	
	
input(' ')
