#!/bin/bash

thread_nums=(48 40 32 24 20 16 12 8 4 2 1)

for thread_num in "${thread_nums[@]}"
do
	export OMP_NUM_THREADS=$thread_num
	echo "Running with $thread_num threads..."
    	if ! ./mandelbrotset_data
    	then
        	echo "Error: Execution failed with $thread_num threads."
        	exit 1
    	fi
done
