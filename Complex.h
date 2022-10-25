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
    // Конструктори
    Complex(const T& real, const T& imaginary) : real(real), imaginary(imaginary) {}

    explicit Complex(const T& number) : real(number), imaginary(0) {}

    Complex() : real(0), imaginary(0) {}

    // Гетери
    inline T getReal() {
        return this->real;
    }

    inline T getImaginary() {
        return this->imaginary;
    }

    // Сетери
    inline void setReal(const T& realPart) {
        this->real = realPart;
    }

    inline void setImaginary(const T& imaginaryPart) {
        this->imaginary = imaginaryPart;
    }

    // Видрукувати число
    inline void print() {
        if (this->imaginary >= 0) {
            cout << this->real << " + " << this->imaginary << " i " << "  ";
        }
        else {
            cout << this->real << " - " << abs(this->imaginary) << " i " << "  ";
        }
    }

    // Додавання
    inline Complex<T> operator + (const T& number) {
        return Complex<T>(this->real + number, this->imaginary);
    }

    inline Complex<T> operator + (const Complex<T>& C1) {
        return Complex<T>(this->real + C1.real, this->imaginary + C1.imaginary);
    }

    inline Complex<T>& operator += (const T& number) {
        this->real = this->real + number;

        this->imaginary = this->imaginary + number;
        return *this;
    }

    inline Complex<T>& operator += (const Complex<T>& C1) {
        this->real = this->real + C1.real;

        this->imaginary = this->imaginary + C1.imaginary;
        return *this;
    }

    // Віднімання
    inline Complex<T> operator - (const T& number) {
        return Complex<T>(this->real - number, this->imaginary);
    }

    inline Complex<T> operator - (const Complex<T>& C1) {
        return Complex<T>(this->real - C1.real, this->imaginary - C1.imaginary);
    }

    inline Complex<T>& operator -= (const T& number) {
        this->real = this->real - number;

        this->imaginary = this->imaginary - number;
        return *this;
    }

    inline Complex<T>& operator -= (const Complex<T>& C1) {
        this->real = this->real - C1.real;

        this->imaginary = this->imaginary - C1.imaginary;
        return *this;
    }

    // Множення
    inline Complex<T> operator * (const T& number) {
        return Complex<T>(this->real * number, this->imaginary * number);
    }

    inline Complex<T> operator * (const Complex<T>& C1) {
        T a = this->real;
        T b = this->imaginary;
        return Complex<T>(a * C1.real - b * C1.imaginary, b * C1.real + a * C1.imaginary);
    }

    inline Complex<T>& operator *= (const T& number) {
        this->real *= number;
        this->imaginary *= number;
        return *this;
    }

    inline Complex<T>& operator *= (const Complex<T>& C1) {
        T a = this->real;
        T b = this->imaginary;
        this->real = a * C1.real - b * C1.imaginary;
        this->imaginary = b * C1.real + a * C1.imaginary;
        return *this;
    }

    // Ділення
    inline Complex<T> operator / (const T& number) {
        if (number) {
            return Complex<T>(this->real / number, this->imaginary / number);
        }
        printError(CANNOT_DIVIDE_BY_ZERO_ERROR_CODE);
        return (*this);
    }

    inline Complex<T> operator / (const Complex<T>& C1) {
        if (C1.real != 0 || C1.imaginary != 0) {
            T a = this->real;
            T b = this->imaginary;
            Complex<T> temp;
            temp.real = (a * C1.real + b * C1.imaginary)
                        / (C1.real * C1.real + C1.imaginary * C1.imaginary);
            temp.imaginary = (b * C1.real - a * C1.imaginary)
                             / (C1.real * C1.real + C1.imaginary * C1.imaginary);
            return temp;
        }
        printError(CANNOT_DIVIDE_BY_ZERO_ERROR_CODE);
        return (*this);
    }

    inline Complex<T>& operator /= (const T& number) {
        if (number) {
            this->real /= number;
            this->imaginary /= number;
            return *this;
        }
        printError(CANNOT_DIVIDE_BY_ZERO_ERROR_CODE);
        return *this;
    }

    inline Complex<T>& operator /= (const Complex<T>& C1) {
        if (C1.real != 0 || C1.imaginary != 0) {
            T a = this->real;
            T b = this->imaginary;
            this->real = (a * C1.real + b * C1.imaginary)
                         / (C1.real * C1.real + C1.imaginary * C1.imaginary);

            this->imaginary = (b * C1.real - a * C1.imaginary)
                              / (C1.real * C1.real + C1.imaginary * C1.imaginary);
            return *this;
        }
        printError(CANNOT_DIVIDE_BY_ZERO_ERROR_CODE);
        return *this;
    }

    // Присвоєння
    inline Complex<T>& operator = (const Complex& value) {
        this->real = value.real;
        this->imaginary = value.imaginary;
        return *this;
    }

    inline Complex<T>& operator = (const T& number) {
        this->real = number;
        this->imaginary = 0;
        return *this;
    }

    // Порівняння
    inline bool operator == (const Complex<T>& C1) {
        if ((this->real == C1.real && this->imaginary == C1.imaginary)) {
            return true;
        }
        return false;
    }

    inline bool operator == (const T& number) {
        if ((this->real == number && this->imaginary == number)) {
            return true;
        }
        return false;
    }

    inline bool operator != (const Complex<T>& C1) {
        if ((this->real != C1.real || this->imaginary != C1.imaginary)) {
            return true;
        }
        return false;
    }

    inline bool operator != (const T& number) {
        if ((this->real != number || this->imaginary != number)) {
            return true;
        }
        return false;
    }

    inline bool operator < (const Complex<T>& C1) {
        if (this->real < C1.real || ((this->real = C1.real) && this->imaginary < C1.imaginary)) {
            return true;
        }
        return false;
    }

    inline bool operator <= (const Complex<T>& C1) {
        if ((this->real < C1.real || ((this->real = C1.real) && this->imaginary < C1.imaginary))
            || ((this->real = C1.real) && (this->imaginary = C1.imaginary))) {
            return true;
        }
        return false;
    }


    inline bool operator > (const Complex<T>& C1) {
        if (this->real > C1.real || ((this->real = C1.real) && this->imaginary > C1.imaginary)) {
            return true;
        }
        return false;
    }

    inline bool operator >= (const Complex<T>& C1) {
        if ((this->real > C1.real || ((this->real = C1.real) && this->imaginary > C1.imaginary))
             ((this->real = C1.real) && (this->imaginary = C1.imaginary))) {
            return true;
        }
        return false;
    }

    // Перевантаження операторів вводу/виводу
    inline friend ostream& operator << (ostream& out, Complex<T>& complex)
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

    inline friend istream& operator >> (istream& in, Complex<T>& complex)
    {
        cout << "Real:";
        in >> complex.real;
        cout << "Imagine:";
        in >> complex.imaginary;
        return in;
    }
};

#endif //ALGORITHMSGROUPPROJECT_COMPLEX_H
