#ifndef MANDELBROT_XMESH_H
#define MANDELBROT_XMESH_H

#include <omp.h>
#include "mandelbrot.h"


class mandelbrot_xmesh : public mandelbrot
{
public:
	mandelbrot_xmesh(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys);
	mandelbrot_xmesh(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, const thread_config& _thread_config);
	mandelbrot_xmesh(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, const std::string& _file_name);
	mandelbrot_xmesh(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, const thread_config& _thread_config, const std::string& _file_name);
	mandelbrot_xmesh(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, const int& _n_threads_x, const int& n_threads_y, const std::string& _file_name);

	void calculate(const double& _scale);
	void calculate();

protected:

	int omp_num_threads, thread_id, size_per_thread;
	int* first_range, * last_range;
	
};


#endif