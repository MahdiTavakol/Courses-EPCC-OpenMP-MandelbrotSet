#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <omp.h>

#include "Complex.h"

template <typename T>
void allocate(T**& Coors, const int& size_x, const int& size_y);
template <typename T>
void deallocate(T**& Coors);

int main(int argc, char** argv)
{
	// Usage ./mandelbrotset_data_anim  x_min x_max y_min y_max
	double x_min, x_max, y_min, y_max;
	int x_size = 1920;
	int y_size = 1080;
	int num_iterations = 2000;
	double scale = 1.0;
	double zero = 0.0;
	complex c(0.0);
	complex z(0.0);
	int serial_mode = 1;


	std::ofstream file, file_omp;
	std::string file_name = "Mandelbrot";
	std::string file_omp_name = "Mandelbrot_omp";

	x_min = -3.56;
	x_max = 1.77;
	y_min = -1.5;
	y_max = 1.5;

	double** X;
	allocate(X, x_size, y_size);

	if (argc == 5)
	{
		x_min = std::stof(argv[1]);
		x_max = std::stof(argv[2]);
		y_min = std::stof(argv[3]);
		y_max = std::stof(argv[4]);
	}
	else if (argc == 2)
	{
		scale = std::stof(argv[1]);
		x_min *= scale;
		x_max *= scale;
		y_min *= scale;
		y_max *= scale;
	}
	else if (argc == 5)
	{
		x_center = std::stof(argv[1]);
		y_center = std::stof(argv[2]);
		scale = std::stof(argv[3]);
		serial_mode = std::stoi(argv[4]);
		x_min = scale * (x_min + x_center);
		x_max = scale * (x_max + x_center);
		y_min = scale * (y_min + y_center);
		y_max = scale * (y_max + y_center);

	}
	else
		std::cerr << "Usage ./mandelbrotset_data_anim  x_min x_max y_min y_max \
                         or ./mandelbrotset_data_anim scale \
                         or ./mandelbrotset_data_anim x_center y_center scale omp_mode" << std::endl;

	std::stringstream iss;
	std::string scale_str;
	iss << std::fixed << std::setprecision(4) << scale;
	iss >> scale_str;


	file_name = file_name + "_" + scale_str + ".dat";
	file_omp_name = file_omp_name + "_" + scale_str + ".dat";
	file.open(file_name);
	file_omp.open(file_omp_name);



	if (!file.is_open())
	{
		std::cout << "Error: Cannot open " << file_name << " for writing" << std::endl;
		return -1;
	}
	if (!file_omp.is_open())
	{
		std::cout << "Error: Cannot open " << file_omp_name << " for writing" << std::endl;
		return -1;
	}


	if (serial_mode)
	{
		std::cout << "Starting the serial code" << std::endl;

		double area = 0;

		// Row bases similar to our allocation
		for (int j = 0; j < y_size; j++)
			for (int i = 0; i < x_size; i++)
			{
				z.real = 0.0;
				z.imag = 0.0;
				c.real = x_min + (double)i * (x_max - x_min) / (x_size - 1);
				c.imag = y_min + (double)j * (y_max - y_min) / (y_size - 1);
				int k = 0;
				for (k = 0; k < num_iterations; k++)
				{
					z = z * z + c;
					if (z.abs_complex() > 2.0) break;
				}
				if (k == num_iterations)
				{
					area = area + 1;
				}
				X[i][j] = ((double)k / (double)num_iterations);
			}

		std::cout << "The area of the set is " << area << std::endl;

		std::cout << "Writting the output " << std::endl;

		for (int j = 0; j < y_size; j++)
		{
			for (int i = 0; i < x_size - 1; i++)
				file << X[i][j] << ",";
			file << X[x_size - 1][j] << std::endl;
		}


		std::cout << "Finished writing the output" << std::endl;

	}

	std::cout << "Starting the parallel code" << std::endl;


	area = 0.0;

#pragma omp parallel for default(none) shared(x_size,x_min,x_max,y_min,y_max,y_size,num_iterations,file_omp,X) private(z,c) reduction(+:area)
	for (int j = 0; j < y_size; j++)
	{
		for (int i = 0; i < x_size; i++)
		{
			z.real = 0.0;
			z.imag = 0.0;
			c.real = x_min + (double)i * (x_max - x_min) / (x_size - 1);
			c.imag = y_min + (double)j * (y_max - y_min) / (y_size - 1);
			int k = 0;
			for (k = 0; k < num_iterations; k++)
			{
				z = z * z + c;
				if (z.abs_complex() > 2.0) break;
			}
			if (k == num_iterations)
			{
				area = area + 1;
			}
			X[i][j] = ((double)k / (double)num_iterations);
		}
	}

	std::cout << "The area of the set is " << area << std::endl;

	std::cout << "Writting the output " << std::endl;

	for (int j = 0; j < y_size; j++)
	{
		for (int i = 0; i < x_size - 1; i++)
			file_omp << X[i][j] << ",";
		file_omp << X[x_size - 1][j] << std::endl;
	}
	std::cout << "Finished writing the output" << std::endl;

	std::cout << "Cleaning up!" << std::endl;

	deallocate(X);
	file.close();
	file_omp.close();


	return 0;

}


template <typename T>
void allocate(T**& Coors, const int& size_x, const int& size_y)
{
	T* Temp = (T*)malloc(size_x * size_y * sizeof(T));
	Coors = (T**)malloc(size_x * sizeof(T*)); // row_based for now

	int n = 0;
	for (int i = 0; i < size_x; i++)
	{
		Coors[i] = &Temp[n];
		n += size_y;
	}
}


template <typename T>
void deallocate(T**& Coors)
{
	free(Coors[0]); // Since the memory is continues, deallocating the first one will delete the whole memory
	free(Coors);
}
