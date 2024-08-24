#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

template <typename T>
class complex {
public:
    complex();  // Default constructor
    complex(T _real, T _imag);  // Constructor with real and imaginary parts
    complex(T _real);  // Constructor with only real part

    complex operator+(const complex& arg) const;  // Addition operator
    complex operator*(const complex& arg) const;  // Multiplication operator
    complex& operator=(const complex& arg);  // Assignment operator

    T abs_complex() const;  // Method to calculate the magnitude

    T real, imag;  // Real and imaginary parts
};


template <typename T>
complex<T>::complex() : real(0), imag(0) {}

template <typename T>
complex<T>::complex(T _real, T _imag) : real(_real), imag(_imag) {}

template <typename T>
complex<T>::complex(T _real) : real(_real), imag(0) {}

template <typename T>
complex<T> complex<T>::operator+(const complex<T>& arg) const {
    return complex<T>(this->real + arg.real, this->imag + arg.imag);
}

template <typename T>
complex<T> complex<T>::operator*(const complex<T>& arg) const {
    return complex<T>(this->real * arg.real - this->imag * arg.imag, 
                      this->real * arg.imag + this->imag * arg.real);
}

template <typename T>
complex<T>& complex<T>::operator=(const complex<T>& arg) {
    if (this != &arg) {
        this->real = arg.real;
        this->imag = arg.imag;
    }
    return *this;
}

template <typename T>
T complex<T>::abs_complex() const {
    return sqrt(this->real * this->real + this->imag * this->imag);
}

// Explicit template instantiation (if needed)
// template class complex<int>;
// template class complex<double>;
// template class complex<float>;



#endif // COMPLEX_H
