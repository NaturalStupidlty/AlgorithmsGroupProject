#ifndef ALGORITHMSGROUPPROJECT_COMPLEX_H
#define ALGORITHMSGROUPPROJECT_COMPLEX_H

#include "Errors.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::istream;

template <typename T> class Complex {
private:
    T real;
    T imaginary;
public:
    Complex(const T& real, const T& imaginary) : real(real), imaginary(imaginary) {}

    explicit Complex(const T& number) : real(number), imaginary(number) {}

    Complex() : real(0), imaginary(0) {}

    T getReal() {
        return this->real;
    }

    T getImaginary() {
        return this->imaginary;
    }

    void setReal(const T& realPart) {
        this->real = realPart;
    }

    void setImaginary(const T& imaginaryPart) {
        this->imaginary = imaginaryPart;
    }

    void print() {
        if (this->imaginary >= 0) {
            cout << this->real << " + " << this->imaginary << " i " << "  ";
        }
        else {
            cout << this->real << " - " << this->imaginary << " i " << "  ";
        }
    }

    Complex<T> operator + (const T& number) {
        return Complex<T>(this->real + number, this->imaginary);
    }

    Complex<T> operator + (const Complex<T>& C1) {
        return Complex<T>(this->real + C1.real, this->imaginary + C1.imaginary);
    }

    Complex<T>& operator += (const Complex<T>& C1) {
        this->real = this->real + C1.real;

        this->imaginary = this->imaginary + C1.imaginary;
        return *this;
    }


    Complex<T> operator - (const T& number) {
        return Complex<T>(this->real - number, this->imaginary);
    }

    Complex<T> operator - (const Complex<T>& C1) {
        return Complex<T>(this->real - C1.real, this->imaginary - C1.imaginary);
    }

    Complex<T>& operator -= (const Complex<T>& C1) {
        this->real = this->real - C1.real;

        this->imaginary = this->imaginary - C1.imaginary;
        return *this;
    }


    Complex<T> operator * (const T& number) {
        return Complex<T>(this->real * number, this->imaginary * number);
    }

    Complex<T> operator * (const Complex<T>& C1) {
        T a = this->real;
        T b = this->imaginary;
        return Complex<T>(a * C1.real - b * C1.imaginary, b * C1.real + a * C1.imaginary);
}

    Complex<T>& operator *= (const Complex<T>& C1) {
        T a = this->real;
        T b = this->imaginary;
        this->real = a * C1.real - b * C1.imaginary;
        this->imaginary = b * C1.real + a * C1.imaginary;
        return *this;
    }


    Complex<T> operator / (const T& number) {
        if (number) {
            return Complex<T>(this->real / number, this->imaginary / number);
        }
        printError(2);
        return Complex<T>(0, 0);
    }

    Complex<T> operator / (const Complex<T>& C1) {
        T a = this->real;
        T b = this->imaginary;
        Complex<T> temp;
        temp.real = (a * C1.real + b * C1.imaginary)
                    / (C1.real * C1.real + C1.imaginary * C1.imaginary);
        temp.imaginary = (b * C1.real - a * C1.imaginary)
                         / (C1.real * C1.real + C1.imaginary * C1.imaginary);
        return temp;
    }

    Complex<T>& operator /= (const Complex<T>& C1) {
        T a = this->real;
        T b = this->imaginary;
        this->real = (a * C1.real + b * C1.imaginary)
                       / (C1.real * C1.real + C1.imaginary * C1.imaginary);

        this->imaginary = (b * C1.real - a * C1.imaginary)
                          / (C1.real * C1.real + C1.imaginary * C1.imaginary);
        return *this;
    }


    Complex<T>& operator = (const Complex& value) {
        this->real = value.real;
        this->imaginary = value.imaginary;
        return *this;
    }

    bool operator == (const Complex<T>& C1) {
        if ((this->real == C1.real and this->imaginary == C1.imaginary)) {
            return true;
        }
        return false;
    }

    bool operator == (const T& number) {
        if ((this->real == number and this->imaginary == number)) {
            return true;
        }
        return false;
    }

    bool operator < (const Complex<T>& C1) {
        if (this->real < C1.real or ((this->real = C1.real) and this->imaginary < C1.imaginary)) {
            return true;
        }
        return false;
    }

    bool operator <= (const Complex<T>& C1) {
        if ((this->real < C1.real or ((this->real = C1.real) and this->imaginary < C1.imaginary))
            or ((this->real = C1.real) and (this->imaginary = C1.imaginary))) {
            return true;
        }
        return false;
    }

    bool operator > (const Complex<T>& C1) {
        if (this->real > C1.real or ((this->real = C1.real) and this->imaginary > C1.imaginary)) {
            return true;
        }
        return false;
    }

    bool operator >= (const Complex<T>& C1) {
        if ((this->real > C1.real or ((this->real = C1.real) and this->imaginary > C1.imaginary))
            or ((this->real = C1.real) and (this->imaginary = C1.imaginary))) {
            return true;
        }
        return false;
    }

    friend ostream& operator << (ostream& out, Complex<T>& complex)
    {
        if (complex.real == 0) {
            return out << "i";
        }
        if (complex.imaginary == 1) {
            return out << complex.real <<" + i";
        }
        if (complex.imaginary == -1) {
            return out << complex.real << " - i";
        }
        out << complex.real << " + " << complex.imaginary << "i";
        return out;
    }

    friend istream& operator >> (istream& in, Complex<T>& complex)
    {
        cout << "Real:";
        in >> complex.real;
        cout << "Imagine:";
        in >> complex.imaginary;
        return in;
    }
};

#endif //ALGORITHMSGROUPPROJECT_COMPLEX_H
