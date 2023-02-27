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

/** Complex numbers class
 *
 * @tparam T - type
 */
template <typename T> class Complex {
private:
    T real;
    T imaginary;
public:
    /** Create a number with both realPart and imaginaryPart
     *
     * @param realPart
     * @param imaginaryPart
     */
    Complex(const T& realPart, const T& imaginaryPart) : real(realPart), imaginary(imaginaryPart) {}

    /** Create number only with real part
     *
     * @param number
     */
    explicit Complex(const T& number) : real(number), imaginary(0) {}

    /** Create zero
     *
     */
    Complex() : real(0), imaginary(0) {}

    /** Generate random complex number using uniform_int_distribution
     *
     * @param rangeStart
     * @param rangeEnd
     * @param real - true will create a number only with real part, complex number otherwise
     * @return
     */
    static Complex<T> getRandomNumber(int rangeStart, int rangeEnd, bool real = false)
    {
        std::random_device randomDevice;
        std::mt19937 range(randomDevice());
        std::uniform_int_distribution<T> distance(rangeStart, rangeEnd);
        if (real) {
            return Complex<T>(distance(range));
        }
        return Complex<T>(distance(range), distance(range));
    }

    /** Generate random complex number using uniform_real_distribution
     *
     * @param rangeStart
     * @param rangeEnd
     * @param real - true will create a number only with real part, complex number otherwise
     * @return
     */
    static Complex<T> getRandomNumber(double rangeStart, double rangeEnd, bool real = false)
    {
        std::random_device randomDevice;
        std::mt19937 range(randomDevice());
        std::uniform_real_distribution<T> distance(rangeStart, rangeEnd);
        if (real) {
            return Complex<T>(distance(range));
        }
        return Complex<T>(distance(range), distance(range));
    }

    /** Generate random floating point complex number using uniform_real_distribution
     *
     * @param rangeStart
     * @param rangeEnd
     * @param real - true will create a number only with real part, complex number otherwise
     * @return
     */
    static Complex<T> getRandomNumber(float rangeStart, float rangeEnd, bool real = false)
    {
        std::random_device randomDevice;
        std::mt19937 range(randomDevice());
        std::uniform_int_distribution<T> distance(rangeStart, rangeEnd);
        if (real) {
            return Complex<T>(distance(range));
        }
        return Complex<T>(distance(range), distance(range));
    }

    /** Find absolute value of a complex number as
     * sqrt(real * real + imaginary + imaginary)
     *
     * @return absolute value
     */
    T abs() {
        return sqrt((this->real) * (this->real) + (this->imaginary) * (this->imaginary));
    }

    /** Get real part
     *
     * @return real part
     */
    inline T getReal() {
        return this->real;
    }

    /** Get getImaginary part
     *
     * @return Imaginary part
     */
    inline T getImaginary() {
        return this->imaginary;
    }

    /** Set real part
     *
     * @return real part
     */
    inline void setReal(const T& realPart) {
        this->real = realPart;
    }

    /** Set Imaginary part
     *
     * @return Imaginary part
     */
    inline void setImaginary(const T& imaginaryPart) {
        this->imaginary = imaginaryPart;
    }

    /** Print complex number
     *
     */
    inline void print() {
        if (this->imaginary >= 0) {
            cout << this->real << " + " << this->imaginary << " i " << "  ";
        }
        else {
            cout << this->real << " - " << -this->imaginary << " i " << "  ";
        }
    }

    /** Add regular number
     *
     * @param number - added
     * @return sum
     */
    inline Complex<T> operator + (const T& number) {
        return Complex<T>(this->real + number, this->imaginary);
    }

    /** Add two complex numbers
     *
     * @param complexNumber - added
     * @return sum
     */
    inline Complex<T> operator + (const Complex<T>& complexNumber) {
        return Complex<T>(this->real + complexNumber.real, this->imaginary + complexNumber.imaginary);
    }

    /** Add regular number and rewrite the value
     *
     * @param number  - added
     * @return sum
     */
    inline Complex<T>& operator += (const T& number) {
        this->real = this->real + number;

        this->imaginary = this->imaginary + number;
        return *this;
    }

    /** Add complex number and rewrite the value
     *
     * @param number  - added
     * @return sum
     */
    inline Complex<T>& operator += (const Complex<T>& complexNumber) {
        this->real = this->real + complexNumber.real;

        this->imaginary = this->imaginary + complexNumber.imaginary;
        return *this;
    }

    /** Subtract regular number
     *
     * @param number - subtracted
     * @return difference
     */
    inline Complex<T> operator - (const T& number) {
        return Complex<T>(this->real - number, this->imaginary);
    }

    /** Subtract complex number
     *
     * @param complexNumber - subtracted
     * @return difference
     */
    inline Complex<T> operator - (const Complex<T>& complexNumber) {
        return Complex<T>(this->real - complexNumber.real, this->imaginary - complexNumber.imaginary);
    }

    /** Subtract regular number and rewrite the value
     *
     * @param number  - subtracted
     * @return difference
     */
    inline Complex<T>& operator -= (const T& number) {
        this->real = this->real - number;

        this->imaginary = this->imaginary - number;
        return *this;
    }

    /** Subtract complex number and rewrite the value
     *
     * @param complexNumber  - subtracted
     * @return difference
     */
    inline Complex<T>& operator -= (const Complex<T>& complexNumber) {
        this->real = this->real - complexNumber.real;

        this->imaginary = this->imaginary - complexNumber.imaginary;
        return *this;
    }

    /** Multiply by regular number
     *
     * @param number - factor
     * @return product
     */
    inline Complex<T> operator * (const T& number) {
        return Complex<T>(this->real * number, this->imaginary * number);
    }

    /** Multiply by complex number
     *
     * @param complexNumber - factor
     * @return product
     */
    inline Complex<T> operator * (const Complex<T>& complexNumber) {
        T a = this->real;
        T b = this->imaginary;
        return Complex<T>(a * complexNumber.real - b * complexNumber.imaginary, b * complexNumber.real + a * complexNumber.imaginary);
    }

    /** Multiply by regular number and rewrite the value
     *
     * @param number - factor
     * @return product
     */
    inline Complex<T>& operator *= (const T& number) {
        this->real *= number;
        this->imaginary *= number;
        return *this;
    }

    /** Multiply by complex number and rewrite the value
     *
     * @param complexNumber - factor
     * @return product
     */
    inline Complex<T>& operator *= (const Complex<T>& complexNumber) {
        T a = this->real;
        T b = this->imaginary;
        this->real = a * complexNumber.real - b * complexNumber.imaginary;
        this->imaginary = b * complexNumber.real + a * complexNumber.imaginary;
        return *this;
    }

    /** Divide by regular number
     *
     * @param number - divider
     * @return result
     */
    inline Complex<T> operator / (const T& number) {
        if (number) {
            return Complex<T>(this->real / number, this->imaginary / number);
        }
        printError(CANNOT_DIVIDE_BY_ZERO_ERROR_CODE);
        return (*this);
    }

    /** Divide by complex number
     *
     * @param complexNumber - divider
     * @return result
     */
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

    /** Divide by regular number and rewrite the value
     *
     * @param number - divider
     * @return result
     */
    inline Complex<T>& operator /= (const T& number) {
        if (number) {
            this->real /= number;
            this->imaginary /= number;
            return *this;
        }
        printError(CANNOT_DIVIDE_BY_ZERO_ERROR_CODE);
        return *this;
    }

    /** Divide by complex number and rewrite the value
     *
     * @param complexNumber - divider
     * @return result
     */
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

    /** Rewrite the value
     *
     * @param complexNumber - new complex value
     * @return changed value
     */
    inline Complex<T>& operator = (const Complex& complexNumber) {
        this->real = complexNumber.real;
        this->imaginary = complexNumber.imaginary;
        return *this;
    }

    /** Rewrite the value
     *
     * @param complexNumber - new regular value
     * @return changed value
     */
    inline Complex<T>& operator = (const T& number) {
        this->real = number;
        this->imaginary = 0;
        return *this;
    }

    /** Compare two complex numbers
     *
     * @param complexNumber - compared value
     * @return true, if they are equal false if not
     */
    inline bool operator == (const Complex<T>& complexNumber) {
        if ((this->real == complexNumber.real && this->imaginary == complexNumber.imaginary)) {
            return true;
        }
        return false;
    }

    /** Compare with regular number
     *
     * @param number - compared value
     * @return true, if they are equal false if not
     */
    inline bool operator == (const T& number) {
        if ((this->real == number && this->imaginary == number)) {
            return true;
        }
        return false;
    }


    /** Compare two complex numbers
     *
     * @param complexNumber - compared value
     * @return false, if they are equal true if not
     */
    inline bool operator != (const Complex<T>& complexNumber) {
        if ((this->real != complexNumber.real || this->imaginary != complexNumber.imaginary)) {
            return true;
        }
        return false;
    }

    /** Compare with regular number
     *
     * @param number - compared value
     * @return false, if they are equal true if not
     */
    inline bool operator != (const T& number) {
        if ((this->real != number || this->imaginary != number)) {
            return true;
        }
        return false;
    }

    /** Compare two complex numbers
     *
     * @param complexNumber - compared value
     * @return true, if first is less than complexNumber, false if not
     */
    inline bool operator < (const Complex<T>& complexNumber) {
        if (this->real < complexNumber.real || ((this->real = complexNumber.real) && this->imaginary < complexNumber.imaginary)) {
            return true;
        }
        return false;
    }

    /** Compare with regular number
     *
     * @param number - compared value
     * @return true, if first is less than complexNumber, false if not
     */
    inline bool operator < (const T& number) {
        return *this < Complex<T>(number);
    }

    /** Compare two complex numbers
     *
     * @param complexNumber - compared value
     * @return true, if first is less or equal than complexNumber, false if not
     */
    inline bool operator <= (const Complex<T>& complexNumber) {
        if ((this->real < complexNumber.real || ((this->real = complexNumber.real) && this->imaginary < complexNumber.imaginary))
            || ((this->real = complexNumber.real) && (this->imaginary = complexNumber.imaginary))) {
            return true;
        }
        return false;
    }

    /** Compare with regular number
     *
     * @param number - compared value
     * @return true, if first is less or equal than complexNumber, false if not
     */
    inline bool operator <= (const T& number) {
        return *this <= Complex<T>(number);
    }

    /** Compare two complex numbers
     *
     * @param complexNumber - compared value
     * @return true, if first is more than complexNumber, false if not
     */
    inline bool operator > (const Complex<T>& complexNumber) {
        if (this->real > complexNumber.real || ((this->real = complexNumber.real) && this->imaginary > complexNumber.imaginary)) {
            return true;
        }
        return false;
    }

    /** Compare with regular number
     *
     * @param number - compared value
     * @return true, if first is more than complexNumber, false if not
     */
    inline bool operator > (const T& number) {
        return *this > Complex<T>(number);
    }

    /** Compare two complex numbers
     *
     * @param complexNumber - compared value
     * @return true, if first is more or equal than complexNumber, false if not
     */
    inline bool operator >= (const Complex<T>& complexNumber) {
        if ((this->real > complexNumber.real || ((this->real = complexNumber.real) && this->imaginary > complexNumber.imaginary))
             ((this->real = complexNumber.real) && (this->imaginary = complexNumber.imaginary))) {
            return true;
        }
        return false;
    }

    /** Compare with regular number
     *
     * @param number - compared value
     * @return true, if first is more or equal than complexNumber, false if not
     */
    inline bool operator >= (const T& number) {
        return *this >= Complex<T>(number);
    }

    /** ostream overloading
     *
     * @param out - stream
     * @param complexNumber - streamed value
     * @return stream
     */
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

    /** istream overloading
     *
     * @param in - stream
     * @param complexNumber - streamed value
     * @return stream
     */
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
