#!/usr/bin/env ruby

# List of thread numbers to iterate over
thread_nums = [48, 40, 32, 24, 20, 16, 12, 8, 4, 2, 1]

# Loop over each thread number
thread_nums.each do |thread_num|
  # Set the OMP_NUM_THREADS environment variable
  ENV['OMP_NUM_THREADS'] = thread_num.to_s

  # Print the current number of threads being used
  puts "Running with #{thread_num} threads..."

  # Execute the command and check if it succeeds
  if !system('./mandelbrotset_data')
    puts "Error: Execution failed with #{thread_num} threads."
    exit 1
  end
end
