#!/bin/bash

thread_nums=(1 2 4 8 12 16 20 24 32 40 48)

for thread_num in "${thread_nums[@]}"
do
	export OMP_NUM_THREADS=$thread_num
	./mandelbrotset_data
done
