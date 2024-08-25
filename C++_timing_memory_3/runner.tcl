#!/usr/bin/env tclsh

# List of thread numbers to iterate over
set thread_nums {48 40 32 24 20 16 12 8 4 2 1}

# Loop over each thread number
foreach thread_num $thread_nums {
    # Set the OMP_NUM_THREADS environment variable
    setenv OMP_NUM_THREADS $thread_num

    # Print the current number of threads being used
    puts "Running with $thread_num threads..."

    # Execute the command and check if it succeeds
    if {[catch {exec ./mandelbrotset_data} result]} {
        puts "Error: Execution failed with $thread_num threads."
        exit 1
    }
}
