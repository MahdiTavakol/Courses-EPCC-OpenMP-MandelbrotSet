#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

class complex {
public:
    complex() : real(0.0), imag(0.0) {}
    complex(double _real, double _imag) : real(_real), imag(_imag) {}
    complex(double _real) : real(_real), imag(0) {}

    complex operator+(const complex& arg) const {
        return complex(this->real + arg.real, this->imag + arg.imag);
    }
    complex operator*(const complex& arg) const {
        return complex(this->real * arg.real - this->imag * arg.imag,
            this->real * arg.imag + this->imag * arg.real);
    }
    complex& operator=(const complex& arg) {
        if (this != &arg) {
            this->real = arg.real;
            this->imag = arg.imag;
        }
        return *this;
    }


    double abs_complex() const {
        return sqrt(this->real * this->real + this->imag * this->imag);
    }

    double real, imag;  // Real and imaginary parts
};

#endif


