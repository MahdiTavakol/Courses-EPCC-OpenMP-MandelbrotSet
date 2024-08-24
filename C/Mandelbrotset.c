#include <cmath>
#include <cstdio>

#include <omp.h>

typedef struct { double real, imag;} complex;


// There is no operator overloading in c
complex dot(const complex& first, const complex& second);
complex add(const complex& first, const complex& second);
double abs(const complex& in);


int main(int argc, char** argv)
{
	int num_points = 20000;
	int num_iterations = 2000;
	complex c, z;
	

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
				z = dot(z, z);
				z = add(z, c);
				//printf("At iteration %d the abs(z) is %f\n",k,abs(z));
				if (abs(z) > 2.0) break;
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
				z = dot(z, z);
				z = add(z, c);
				if (abs(z) > 2.0) break;
			}
			if (k == num_iterations) area = area + 1;
		}
	}

	printf("The area of the set is %f\n", area);
	
	return 0;

}

complex dot(const complex& first, const complex& second)
{
	complex output;
	output.real = first.real * second.real - first.imag * second.imag;
	output.imag = first.real * second.imag + first.imag * second.real;
	return output;
}

complex add(const complex& first, const complex& second)
{
	complex output;
	output.real = first.real + second.real;
	output.imag = first.imag + second.imag;
	return output;
}

double abs(const complex& in)
{
	return abs(in.real * in.real + in.imag * in.imag);
}
