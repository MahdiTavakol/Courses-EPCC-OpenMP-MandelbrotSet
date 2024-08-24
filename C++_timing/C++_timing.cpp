#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>

#include <omp.h>

#include "Complex.h"

template <typename T>
void allocate(T**& Coors, const int& size_x, const int& size_y);
template <typename T>
void deallocate(T**& Coors);

int main(int argc, char** argv)
{
	const double x_min = -3.56;
	const double x_max = 1.77;
	const double y_min = -1.5;
	const double y_max = 1.5;
	int x_size = 1920;
	int y_size = 1080;
	int num_iterations = 10000;
	double zero = 0.0;
	complex c(0.0);
	complex z(0.0);
	std::ofstream file("Mandelbrot.dat");
	std::ofstream file_omp("Mandelbrot_omp.dat");

	double** X;
	allocate(X, x_size, y_size);



	if (!file.is_open())
	{
		std::cout << "Error: Cannot open Mandelbrot.dat for writing" << std::endl;
		return 0;
	}
	if (!file_omp.is_open())
	{
		std::cout << "Error: Cannot open Mandelbrot_omp.dat for writing" << std::endl;
		return 0;
	}


	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
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

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> timeRequired = (end - start);

	//Let's get milliseconds out of that, and report
	std::cout << "The serial code took " << timeRequired.count() << " milliseconds." << std::endl;



	std::cout << "Writting the output " << std::endl;

	for (int j = 0; j < y_size; j++)
	{
		for (int i = 0; i < x_size - 1; i++)
			file << X[i][j] << ",";
		file << X[x_size - 1][j] << std::endl;
	}


	std::cout << "Finished writing the output" << std::endl;


	start = std::chrono::high_resolution_clock::now();
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

	end = std::chrono::high_resolution_clock::now();

	timeRequired = (end - start);

	//Let's get milliseconds out of that, and report
	std::cout << "The omp code took " << timeRequired.count() << " milliseconds." << std::endl;


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
