#ifndef ALGORITHMSGROUPPROJECT_COMPLEX_H
#define ALGORITHMSGROUPPROJECT_COMPLEX_H

#include "Errors.h"
#include <iostream>
#include <random>
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
    Complex(const T& realPart, const T& imaginaryPart) : real(realPart), imaginary(imaginaryPart) {}

    explicit Complex(const T& number) : real(number), imaginary(0) {}

    Complex() : real(0), imaginary(0) {}

    // Генерація випадкових чисел
    static Complex<T> getRandomNumber(T rangeStart, T rangeEnd, bool real = false)
    {
        std::random_device randomDevice;
        std::mt19937 range(randomDevice());
        std::uniform_real_distribution<T> distance(rangeStart, rangeEnd);
        if (real) {
            return Complex<T>(distance(range));
        }
        return Complex<T>(distance(range), distance(range));
    }

    // Модуль числа
    T abs() {
        return sqrt((this->real) * (this->real) + (this->imaginary) * (this->imaginary));
    }

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
            cout << this->real << " - " << -this->imaginary << " i " << "  ";
        }
    }

    // Додавання
    inline Complex<T> operator + (const T& number) {
        return Complex<T>(this->real + number, this->imaginary);
    }

    inline Complex<T> operator + (const Complex<T>& complexNumber) {
        return Complex<T>(this->real + complexNumber.real, this->imaginary + complexNumber.imaginary);
    }

    inline Complex<T>& operator += (const T& number) {
        this->real = this->real + number;

        this->imaginary = this->imaginary + number;
        return *this;
    }

    inline Complex<T>& operator += (const Complex<T>& complexNumber) {
        this->real = this->real + complexNumber.real;

        this->imaginary = this->imaginary + complexNumber.imaginary;
        return *this;
    }

    // Віднімання
    inline Complex<T> operator - (const T& number) {
        return Complex<T>(this->real - number, this->imaginary);
    }

    inline Complex<T> operator - (const Complex<T>& complexNumber) {
        return Complex<T>(this->real - complexNumber.real, this->imaginary - complexNumber.imaginary);
    }

    inline Complex<T>& operator -= (const T& number) {
        this->real = this->real - number;

        this->imaginary = this->imaginary - number;
        return *this;
    }

    inline Complex<T>& operator -= (const Complex<T>& complexNumber) {
        this->real = this->real - complexNumber.real;

        this->imaginary = this->imaginary - complexNumber.imaginary;
        return *this;
    }

    // Множення
    inline Complex<T> operator * (const T& number) {
        return Complex<T>(this->real * number, this->imaginary * number);
    }

    inline Complex<T> operator * (const Complex<T>& complexNumber) {
        T a = this->real;
        T b = this->imaginary;
        return Complex<T>(a * complexNumber.real - b * complexNumber.imaginary, b * complexNumber.real + a * complexNumber.imaginary);
    }

    inline Complex<T>& operator *= (const T& number) {
        this->real *= number;
        this->imaginary *= number;
        return *this;
    }

    inline Complex<T>& operator *= (const Complex<T>& complexNumber) {
        T a = this->real;
        T b = this->imaginary;
        this->real = a * complexNumber.real - b * complexNumber.imaginary;
        this->imaginary = b * complexNumber.real + a * complexNumber.imaginary;
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

    inline Complex<T> operator / (const Complex<T>& complexNumber) {
        if (complexNumber.real != 0 || complexNumber.imaginary != 0) {
            T a = this->real;
            T b = this->imaginary;
            Complex<T> temp;
            temp.real = (a * complexNumber.real + b * complexNumber.imaginary)
                        / (complexNumber.real * complexNumber.real + complexNumber.imaginary * complexNumber.imaginary);
            temp.imaginary = (b * complexNumber.real - a * complexNumber.imaginary)
                             / (complexNumber.real * complexNumber.real + complexNumber.imaginary * complexNumber.imaginary);
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

    inline Complex<T>& operator /= (const Complex<T>& complexNumber) {
        if (complexNumber.real != 0 || complexNumber.imaginary != 0) {
            T a = this->real;
            T b = this->imaginary;
            this->real = (a * complexNumber.real + b * complexNumber.imaginary)
                         / (complexNumber.real * complexNumber.real + complexNumber.imaginary * complexNumber.imaginary);

            this->imaginary = (b * complexNumber.real - a * complexNumber.imaginary)
                              / (complexNumber.real * complexNumber.real + complexNumber.imaginary * complexNumber.imaginary);
            return *this;
        }
        printError(CANNOT_DIVIDE_BY_ZERO_ERROR_CODE);
        return *this;
    }

    // Присвоєння
    inline Complex<T>& operator = (const Complex& complexNumber) {
        this->real = complexNumber.real;
        this->imaginary = complexNumber.imaginary;
        return *this;
    }

    inline Complex<T>& operator = (const T& number) {
        this->real = number;
        this->imaginary = 0;
        return *this;
    }

    // Порівняння
    inline bool operator == (const Complex<T>& complexNumber) {
        if ((this->real == complexNumber.real && this->imaginary == complexNumber.imaginary)) {
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


    inline bool operator != (const Complex<T>& complexNumber) {
        if ((this->real != complexNumber.real || this->imaginary != complexNumber.imaginary)) {
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


    inline bool operator < (const Complex<T>& complexNumber) {
        if (this->real < complexNumber.real || ((this->real = complexNumber.real) && this->imaginary < complexNumber.imaginary)) {
            return true;
        }
        return false;
    }

    inline bool operator < (const T& number) {
        return *this < Complex<T>(number);
    }

    inline bool operator <= (const Complex<T>& complexNumber) {
        if ((this->real < complexNumber.real || ((this->real = complexNumber.real) && this->imaginary < complexNumber.imaginary))
            || ((this->real = complexNumber.real) && (this->imaginary = complexNumber.imaginary))) {
            return true;
        }
        return false;
    }

    inline bool operator <= (const T& number) {
        return *this <= Complex<T>(number);
    }


    inline bool operator > (const Complex<T>& complexNumber) {
        if (this->real > complexNumber.real || ((this->real = complexNumber.real) && this->imaginary > complexNumber.imaginary)) {
            return true;
        }
        return false;
    }

    inline bool operator > (const T& number) {
        return *this > Complex<T>(number);
    }

    inline bool operator >= (const Complex<T>& complexNumber) {
        if ((this->real > complexNumber.real || ((this->real = complexNumber.real) && this->imaginary > complexNumber.imaginary))
             ((this->real = complexNumber.real) && (this->imaginary = complexNumber.imaginary))) {
            return true;
        }
        return false;
    }

    inline bool operator >= (const T& number) {
        return *this >= Complex<T>(number);
    }

    // Перевантаження операторів вводу/виводу
    inline friend ostream& operator << (ostream& out, Complex<T>& complexNumber)
    {
        if (complexNumber.real == 0) {
            return out << "i";
        }
        if (complexNumber.imaginary == 1) {
            return out << complexNumber.real <<" + i";
        }
        if (complexNumber.imaginary == -1) {
            return out << complexNumber.real << " - i";
        }
        out << complexNumber.real << " + " << complexNumber.imaginary << "i";
        return out;
    }

    inline friend istream& operator >> (istream& in, Complex<T>& complexNumber)
    {
        cout << "Real:";
        in >> complexNumber.real;
        cout << "Imagine:";
        in >> complexNumber.imaginary;
        return in;
    }
};

#endif //ALGORITHMSGROUPPROJECT_COMPLEX_H
