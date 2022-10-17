#ifndef ALGORITHMSGROUPPROJECT_COMPLEX_H
#define ALGORITHMSGROUPPROJECT_COMPLEX_H

#include <vector>
#include <iostream>

using std::cout;
using std::endl;

template <typename T> class Complex
{
    T real;
    T imaginary;
public:
    Complex(T real, T imaginary) : real(real), imaginary(imaginary) {}

    explicit Complex(T number) : real(number), imaginary(number) {}

    Complex() : real(0), imaginary(0) {}

    Complex<T> operator + (const Complex<T>& C1)
    {
        return Complex<T>(this->real + C1.real, this->imaginary + C1.imaginary);
    }

    Complex<T> operator + (T number)
    {
        return Complex<T>(this->real + number, this->imaginary);
    }

    Complex<T>& operator += (const Complex<T>& C1)
    {
        // adding real part of complex numbers
        this->real = this->real + C1.real;

        // adding imaginary part of complex numbers
        this->imaginary = this->imaginary + C1.imaginary;
        return *this;
    }

    Complex<T> operator - (const Complex<T>& C1)
    {
        return Complex<T>(this->real - C1.real, this->imaginary - C1.imaginary);
    }

    Complex<T> operator - (T number)
    {
        return Complex<T>(this->real - number, this->imaginary);
    }

    Complex<T>& operator -= (const Complex<T>& C1)
    {
        // adding real part of complex numbers
        this->real = this->real - C1.real;

        // adding imaginary part of complex numbers
        this->imaginary = this->imaginary - C1.imaginary;
        return *this;
    }

    Complex<T> operator * (const Complex<T>& C1)
    {
        return Complex<T>(((this->real) * (C1.real)) - ((this->imaginary) * (C1.imaginary)),
                          ((this->real) * (C1.imaginary)) + ((C1.real) * (this->imaginary)));
    }

    Complex<T> operator * (T number)
    {
        return Complex<T>(this->real * number, this->imaginary * number);
    }

    Complex<T>& operator *= (const Complex<T>& C1)
    {
        // multiplying real part of complex numbers
        this->real = ((this->real) * (C1.real)) - ((this->imaginary) * (C1.imaginary));

        // multiplying imaginary part of complex numbers
        this->imaginary = ((this->real) * (C1.imaginary)) + ((C1.real) * (this->imaginary));
        return *this;
    }

    // !!!!bugs ACHTUNG

    Complex<T> operator / (const Complex<T>& C1)
    {
        // creating temporary variable
        Complex<T> temp;

        // dividing real part of complex numbers
        temp.real = ( (this->real * C1.real) + (this->imaginary * C1.imaginary) )
                    / ( (C1.real * C1.real) + (C1.imaginary * C1.imaginary) );

        // dividing imaginary part of complex numbers
        temp.imaginary = ( (this->imaginary + C1.real) - (this->real + C1.imaginary) )
                         / ( (C1.real * C1.real) + (C1.imaginary * C1.imaginary) );

        // returning the sum
        return temp;
    }

    Complex<T> operator / (T number)
    {
        return Complex<T>(this->real / number, this->imaginary / number);
    }

    // !!!!bugs ACHTUNG
    Complex<T>& operator /= (const Complex<T>& C1)
    {
        // dividing real part of complex numbers
        this->real = ( (this->real * C1.real) + (this->imaginary * C1.imaginary) )
                     / ( (C1.real * C1.real) + (C1.imaginary * C1.imaginary) );

        // dividing imaginary part of complex numbers
        this->imaginary = ( (this->imaginary + C1.real) - (this->real + C1.imaginary) )
                          / ( (C1.real * C1.real) + (C1.imaginary * C1.imaginary) );
        return *this;
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

    Complex<T>& operator = (const Complex &value)
    {
        this->real = value.real;
        this->imaginary = value.imaginary;
        return *this;
    }

    T getReal()
    {
        return this->real;
    }

    T getImaginary()
    {
        return this->imaginary;
    }

    void setReal(T realPart)
    {
        this->real = realPart;
    }

    void setImaginary(T imaginaryPart)
    {
        this->imaginary = imaginaryPart;
    }

    void print()
    {
        cout << this->real << " + " << this->imaginary << "i " << "  ";
    }
};

#endif //ALGORITHMSGROUPPROJECT_COMPLEX_H
