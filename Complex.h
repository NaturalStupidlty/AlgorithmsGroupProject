#ifndef ALGORITHMSGROUPPROJECT_COMPLEX_H
#define ALGORITHMSGROUPPROJECT_COMPLEX_H

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

template <typename T> class Complex {
    T real;
    T imaginary;
public:
    Complex(T real, T imaginary) : real(real), imaginary(imaginary) {}

    explicit Complex(T number) : real(number), imaginary(number) {}

    Complex() : real(0), imaginary(0) {}

    T getReal() {
        return this->real;
    }

    T getImaginary() {
        return this->imaginary;
    }

    void setReal(T realPart) {
        this->real = realPart;
    }

    void setImaginary(T imaginaryPart) {
        this->imaginary = imaginaryPart;
    }

    void print() {
        cout << this->real << " + " << this->imaginary << "i " << "  ";
    }

    Complex<T> operator + (T number) {
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

    Complex<T> operator - (T number) {
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

    Complex<T> operator * (T number) {
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

    Complex<T> operator / (T number) {
        return Complex<T>(this->real / number, this->imaginary / number);
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

    Complex<T>& operator = (const Complex &value) {
        this->real = value.real;
        this->imaginary = value.imaginary;
        return *this;
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
};

#endif //ALGORITHMSGROUPPROJECT_COMPLEX_H
