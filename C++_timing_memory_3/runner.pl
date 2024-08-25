#!/usr/bin/env perl

use strict;
use warnings;

# List of thread numbers to iterate over
my @thread_nums = (48, 40, 32, 24, 20, 16, 12, 8, 4, 2, 1);

# Loop over each thread number
foreach my $thread_num (@thread_nums) {
    # Set the OMP_NUM_THREADS environment variable
    $ENV{OMP_NUM_THREADS} = $thread_num;

    # Print the current number of threads being used
    print "Running with $thread_num threads...\n";

    # Execute the command and check if it succeeds
    if (system('./mandelbrotset_data') != 0) {
        print "Error: Execution failed with $thread_num threads.\n";
        exit 1;
    }
}
