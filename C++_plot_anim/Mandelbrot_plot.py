#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import pandas as pd
import sys

#####################################################################
def apply_colormap(c_array,cmap):

	cmap = plt.get_cmap('rainbow')

	rgba = cmap(c_array)
	
	return rgba[:,:,:3]


#####################################################################
def read_data(datafile,x_dim,y_dim,min_c,max_c):
	
	print("\tStart reading the data file")
	df = pd.read_csv(datafile,header=None)
	print("\tFinished reading the data file")

	if df.shape[0] != y_dim or df.shape[1] != x_dim :
		raise ValueError(f"Unexpected dimensions: got ({df.shape[0]}, {df.shape[1]}) but expected ({y_dim}, {x_dim})")
	
	data_array = df.values
	data = np.zeros((y_dim,x_dim,3))

	norm = (data_array - min_c)/(max_c - min_c)
	norm = np.clip(norm,0,1)
	
	
	cmap = plt.get_cmap("rainbow")

	data = apply_colormap(norm,cmap)


	return data

##########################################################################

datafile = sys.argv[1]
x_dim, y_dim = int(sys.argv[2]), int(sys.argv[3])
c_min, c_max = 0 , 1
scale = float(sys.argv[4])
outputwidth , outputheight = 16, 9
datafile = datafile.replace(".dat","")
scale_str = f"{scale:.4f}"
datafile = datafile + "_" + scale_str + ".dat" 
outputfile = datafile.replace(".dat","")

##########################################################################
print("Processing the data file")
data = read_data(datafile,x_dim,y_dim,c_min,c_max)
print("Finished processing the data file")
##########################################################################
print("Plotting the data")
fig, ax = plt.subplots()
ax.imshow(data)
plt.xticks([])
plt.yticks([])

##########################################################################
print("Saving the plot")
fig.set_size_inches(outputwidth,outputheight)
fig.savefig(outputfile+".svg",dpi=1200)

#######################################################################################################
print("All done!")
