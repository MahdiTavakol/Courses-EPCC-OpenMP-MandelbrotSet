A visual studio version of the mandelbrotset code

The array class has several allocation methods which are used to compare the performance of various allocation/deallocation methods

1) C_X_MAJOR ==> Using the malloc[free] method (C) to allocate[deallocate] an x-major array

2) C_Y_MAJOR ==> Using the malloc[free] method (C) to allocate[deallocate] a y-major array

3) CPP_X_MAJOR ==> Using the new[delete] method (C++) to allocate[deallocate] an x-major array

4) CPP_Y_MAJOR ==> Using the new[delete] method (C++) to allocate[deallocate] an y-major array

According to the allocation method an operator() is used to do the indexing. 



There are several mandelbrot class variants inherited from the original one to compare the effect of data arrangement on the performance:

1) mandelbrot_xmesh ==> The data in the x direction is distributed among the threads in the outer loop

2) mandelbrot_ymesh ==> The data in the y direction is distributed among the threads in the outer loop

3) mandelbrot_xmesh_innerloop ==> The data in the x direction is distributed among the threads in the inner loop

4) mandelbrot_ymesh_innerloop ==> The data in the y direction is distributed among the threads in the inner loop

And finally the file timings.xlsx compares the performance of these versions for 
