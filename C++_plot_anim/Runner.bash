#!/bin/bash

export center_x=-0.7435
export center_y=0.1860
scales=(1,0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.09,0.08,0.07,0.06,0.05,0.04,0.03,0.02,0.1,01)

for scale in "${scales[@]}"
do
	./mandelbrotset_data_anim $center_x $center_y $scale 0
	./mandelbrotset_data_anim $scale
done
