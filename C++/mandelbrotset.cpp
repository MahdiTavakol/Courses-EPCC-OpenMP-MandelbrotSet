#include <cmath>
#include <iostream>

#include <omp.h>

#include "Complex.h"


int main(int argc, char** argv)
{
	int num_points = 20000;
	int num_iterations = 2000;
	double zero = 0.0;
	complex c(zero);
	complex z(zero);
	

	printf("Starting the serial code\n");

	double area = 0;

	for (int i = 0; i < num_points; i++)
		for (int j = 0; j < num_points; j++)
		{
			z.real = 0.0;
			z.imag = 0.0;
			c.real = i;
			c.imag = j;
			int k = 0;
			for (k = 0; k < num_iterations; k++)
			{
				z = z*z;
				z = z+c;
				//printf("At iteration %d the abs(z) is %f\n",k,abs(z));
				if (z.abs_complex() > 2.0) break;
			}
			if (k == num_iterations) area = area + 1;
		}

	printf("The area of the set is %f\n", area);

	printf("Starting the parallel code\n");

	area = 0.0;
	
#pragma omp parallel for default(none) shared(num_points,num_iterations) private(z,c) reduction(+:area)
	for (int i = 0; i < num_points; i++)
	{
		for (int j = 0; j < num_points; j++)
		{
			z.real = 0.0;
			z.imag = 0.0;
			c.real = i;
			c.imag = j;
			int k = 0;
			for (k = 0; k < num_iterations; k++)
			{
				z = z*z;
				z = z+c;
				if (z.abs_complex() > 2.0) break;
			}
			if (k == num_iterations) area = area + 1;
		}
	}

	printf("The area of the set is %f\n", area);
	
	return 0;

}
