#ifndef ALGORITHMSGROUPPROJECT_COMPLEX_H
#define ALGORITHMSGROUPPROJECT_COMPLEX_H

#include <vector>
#include <iostream>

using std::cout;
using std::endl;

template <typename T> class Complex
{
public:
    T real;
    T imaginary;

    explicit Complex(T tempReal = 0, T tempImaginary = 0)
    {
        real = tempReal;
        imaginary = tempImaginary;
    }

    Complex operator + (const Complex<T>& C1)
    {
        // creating temporary variable
        Complex temp;

        // adding real part of complex numbers
        temp.real = this->real + C1.real;

        // adding imaginary part of complex numbers
        temp.imaginary = this->imaginary + C1.imaginary;

        // returning the result
        return temp;
    }

    Complex operator - (const Complex<T>& C1)
    {
        // creating temporary variable
        Complex temp;

        // adding real part of complex numbers
        temp.real = this->real - C1.real;

        // adding imaginary part of complex numbers
        temp.imaginary = this->imaginary - C1.imaginary;

        // returning the result
        return temp;
    }

    Complex operator * (const Complex<T>& C1)
    {
        // creating temporary variable
        Complex temp;

        // multiplying real part of complex numbers
        temp.real = ((this->real) * (C1.real)) - ((this->imaginary) * (C1.imaginary));

        // multiplying imaginary part of complex numbers
        temp.imaginary = ((this->real) * (C1.imaginary)) + ((C1.real) * (this->imaginary));

        // returning the result
        return temp;
    }

    Complex operator / (const Complex<T>& C1)
    {
        // creating temporary variable
        Complex temp;

        // dividing real part of complex numbers
        temp.real = ( (this->real * C1.real) + (this->imaginary * C1.imaginary) )
                    / ( (C1.real * C1.real) + (C1.imaginary * C1.imaginary) );

        // dividing imaginary part of complex numbers
        temp.imaginary = ( (this->imaginary + C1.real) - (this->real + C1.imaginary) )
                         / ( (C1.real * C1.real) + (C1.imaginary * C1.imaginary) );

        // returning the sum
        return temp;
    }

    bool operator < (const Complex<T>& C1)
    {
        if (this->real < C1.real or ((this->real = C1.real) and this->imaginary < C1.imaginary))
        {
            return true;
        }
        return false;
    }

    bool operator <= (const Complex<T>& C1)
    {
        if ((this->real < C1.real or ((this->real = C1.real) and this->imaginary < C1.imaginary))
            or ((this->real = C1.real) and (this->imaginary = C1.imaginary)))
        {
            return true;
        }
        return false;
    }

    bool operator > (const Complex<T>& C1)
    {
        if (this->real > C1.real or ((this->real = C1.real) and this->imaginary > C1.imaginary))
        {
            return true;
        }
        return false;
    }

    bool operator >= (const Complex<T>& C1)
    {
        if ((this->real > C1.real or ((this->real = C1.real) and this->imaginary > C1.imaginary))
            or ((this->real = C1.real) and (this->imaginary = C1.imaginary)))
        {
            return true;
        }
        return false;
    }

    void print()
    {
        if (this->imaginary > 0)
        {
            cout << this->real << " + " << this->imaginary << "e ";
        }
        cout << this->real << " - " << this->imaginary << "e ";
    }
};

#endif //ALGORITHMSGROUPPROJECT_COMPLEX_H
