#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>
#include <map>

#include <omp.h>

#include "definitions.h"
#include "array.h"
#include "complex.h"
#include "memory.h"
#include "mandelbrot.h"
#include "mandelbrot_xmesh.h"
#include "mandelbrot_ymesh.h"
#include "mandelbrot_xmesh_innerloop.h"
#include "mandelbrot_ymesh_innerloop.h"


template<class SIMTYPE>
double run_mandelbrot(std::string _info, int _allocation_mode, const bounds& _bnds, 
	const int& _x_size, const int& _y_size, const thread_config& _thread_config, double& area);

void writeMaps(std::string _info_file, std::map<std::string, double>& timings, std::map<std::string, double>& areas);


int main(int argc, char** argv)
{
	bounds bnds;
	bnds.x_min = -3.56;
	bnds.x_max = 1.77;
	bnds.y_min = -1.5;
	bnds.y_max = 1.5;
        int x_size = 1920; 
	int y_size = 1080;

	int allocation_mode;

	int num_threads;
#pragma omp parallel
	{
		num_threads = omp_get_num_threads();
	}

	thread_config trd_cnfg_serial, trd_cnfg_x_meshes, trd_cnfg_y_meshes;

	trd_cnfg_x_meshes.threads_x = num_threads;
	trd_cnfg_x_meshes.threads_y = 1;
	trd_cnfg_y_meshes.threads_x = 1;
	trd_cnfg_y_meshes.threads_y = num_threads;

	std::map<std::string, double> timings;
	std::map<std::string, double> areas;
	std::string timing_area_info_file("timing-area.csv");


	mandelbrot* mndlbrt;
	mndlbrt = nullptr;
	double timing, area;
	allocation_mode = C_X_MAJOR;
	std::string info("1-C_X_MAJOR---serial");
	timing = run_mandelbrot<mandelbrot>(info, allocation_mode,bnds,x_size,y_size, trd_cnfg_serial, area);
	timings[info] = timing;
	areas[info] = area;
	info = "2-C_X_MAJOR---X_MESHES";
	timing = run_mandelbrot<mandelbrot_xmesh>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_x_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	info = "3-C_X_MAJOR---Y_MESHES";
	timing = run_mandelbrot<mandelbrot_ymesh>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_y_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	allocation_mode = C_Y_MAJOR;
	info = "4-C_Y_MAJOR---X_MESHES";
	timing = run_mandelbrot<mandelbrot_xmesh>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_x_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	info = "5-C_Y_MAJOR---Y_MESHES";
	timing = run_mandelbrot<mandelbrot_ymesh>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_y_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	allocation_mode = CPP_X_MAJOR;
	info = "6-CPP_X_MAJOR---serial";
	timing = run_mandelbrot<mandelbrot>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_serial, area);
	timings[info] = timing;
	areas[info] = area;
	info = "7-CPP_X_MAJOR---X_MESHES";
	timing = run_mandelbrot<mandelbrot_xmesh>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_x_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	info = "8-CPP_X_MAJOR---Y_MESHES";
	timing = run_mandelbrot<mandelbrot_ymesh>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_y_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	allocation_mode = CPP_Y_MAJOR;
	info = "9-CPP_Y_MAJOR---X_MESHES";
	timing = run_mandelbrot<mandelbrot_xmesh>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_x_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	info = "10-CPP_Y_MAJOR---Y_MESHES";
	timing = run_mandelbrot<mandelbrot_ymesh>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_y_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	allocation_mode = C_X_MAJOR;
	info = "11-C_X_MAJOR---X_MESHES---OMP_INNER";
	timing = run_mandelbrot<mandelbrot_xmesh_innerloop>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_x_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	info = "12-C_X_MAJOR---Y_MESHES---OMP_INNER";
	timing = run_mandelbrot<mandelbrot_ymesh_innerloop>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_y_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	allocation_mode = C_Y_MAJOR;
	info = "13-C_Y_MAJOR---X_MESHES---OMP_INNER";
	timing = run_mandelbrot<mandelbrot_xmesh_innerloop>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_x_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	info = "14-C_Y_MAJOR---Y_MESHES---OMP_INNER";
	timing = run_mandelbrot<mandelbrot_ymesh_innerloop>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_y_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	allocation_mode = CPP_X_MAJOR;
	info = "15-CPP_X_MAJOR---X_MESHES---OMP_INNER";
	timing = run_mandelbrot<mandelbrot_xmesh_innerloop>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_x_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	info = "16-CPP_X_MAJOR---Y_MESHES---OMP_INNER";
	timing = run_mandelbrot<mandelbrot_ymesh_innerloop>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_y_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	allocation_mode = CPP_Y_MAJOR;
	info = "17-CPP_Y_MAJOR---X_MESHES---OMP_INNER";
	timing = run_mandelbrot<mandelbrot_xmesh_innerloop>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_x_meshes, area);
	timings[info] = timing;
	areas[info] = area;
	info = "18-CPP_Y_MAJOR---Y_MESHES---OMP_INNER";
	timing = run_mandelbrot<mandelbrot_ymesh_innerloop>(info, allocation_mode, bnds, x_size, y_size, trd_cnfg_y_meshes, area);
	timings[info] = timing;
	areas[info] = area;


	writeMaps(timing_area_info_file, timings, areas);

	std::cout << "All done!" << std::endl;

	return 0;
}


template<class SIMTYPE>
double run_mandelbrot(std::string _info, int _allocation_mode, const bounds& _bnds,
	const int& _x_size, const int& _y_size, const thread_config& _thread_config, double& area)
{
	std::cout  << "Allocating the " << _info << " mandlebrot pointer" << std::endl;
	std::string file_name("Mandelbrot_" + _info + ".dat");
	SIMTYPE* mndlbrt;
	mndlbrt = new SIMTYPE(_allocation_mode, _bnds, _x_size, _y_size, _thread_config, file_name);

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	std::cout  << "Starting the " << _info << " code" << std::endl;
    mndlbrt->calculate();
	std::cout  << "Finished the " << _info << " code" << std::endl;
	area = mndlbrt->return_area();
	std::cout << "The area of the set is " << area << std::endl;

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> timeRequired = (end - start);
	//Let's get milliseconds out of that, and report
	std::cout << "The " << _info << " code took " << timeRequired.count() << " milliseconds." << std::endl;



	std::cout << "Writting the output " << std::endl;
	mndlbrt->output();
	std::cout << "Finished writing the output" << std::endl;

	std::cout << "Deallocating the " << _info << " mandlebrot pointer" << std::endl;
	delete mndlbrt;
	mndlbrt = nullptr;

	return timeRequired.count();
}

void writeMaps(std::string _info_file_name, std::map<std::string, double>& _timings, std::map<std::string, double>& _areas)
{
	std::cout << "Writing the timing info file " << std::endl;
	std::ofstream info_file(_info_file_name);

	if (!info_file.is_open())
		std::cerr << "Failed to open the " << _info_file_name << " for writing the timing information" << std::endl;

	info_file << "Run_type,area,timing(ms)" << std::endl;

	if (_timings.size() != _areas.size())
		std::cerr << "The size of the timing (" << _timings.size() << ") and area (" << _areas.size() << ") maps are different which is unexpected" << std::endl;

	auto it1 = _timings.begin();
	auto it2 = _areas.begin();
	for (; it1 != _timings.end() && it2 != _areas.end(); it1++, it2++)
		info_file << it1->first << "," << it2->second << "," << it1->second << std::endl;

	std::cout << "Closing the timing info file " << std::endl;

	info_file.close();
	std::cout << "Finished writing the timging info file " << std::endl;
}


