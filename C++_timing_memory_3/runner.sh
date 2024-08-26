#!/bin/bash

# Define the number of threads to test
thread_nums=(48 40 32 24 20 16 12 8 4 2 1)

# Initialize the CSV file with a header
output_file="timing_results.csv"
echo "num_thread,parallel_time,serial_time" > $output_file

# Loop over each number of threads
for thread_num in "${thread_nums[@]}"
do
    export OMP_NUM_THREADS=$thread_num
    echo "Running with $thread_num threads..."

    # Capture the output of the program
    output=$(./mandelbrotset_data)

    # Check if the program ran successfully
    if [ $? -ne 0 ]; then
        echo "Error: Execution failed with $thread_num threads."
        exit 1
    fi

    # Parse the serial and parallel times from the output, stripping the "milliseconds" word
    serial_time=$(echo "$output" | grep "The serial code took" | awk '{print $5}')
    parallel_time=$(echo "$output" | grep "The omp code took" | awk '{print $5}')

    # Write the results to the CSV file
    echo "$thread_num,${parallel_time% milliseconds},${serial_time% milliseconds}" >> $output_file
done

echo "Timing results written to $output_file"
