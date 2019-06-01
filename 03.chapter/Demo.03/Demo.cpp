// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 
#include <math.h>

template<typename T>
class CComplex
{
    friend T norm(const CComplex<T>& com); 
    friend T abs(const CComplex<T> & com); 
    friend CComplex<T> conj(const CComplex<T>& com); 
    friend CComplex<T> operator+(const CComplex<T>& com1, const CComplex<T>& com2); 
    friend CComplex<T> operator-(const CComplex<T>& com1, const CComplex<T>& com2); 
    friend CComplex<T> operator*(const CComplex<T>& com1, const CComplex<T>& com2); 
    friend CComplex<T> operator/(const CComplex<T>& com1, const CComplex<T>& com2); 
    friend bool operator==(const CComplex<T>& com1, const CComplex<T>& com2); 
    friend bool operator!=(const CComplex<T>& com1, const CComplex<T>& com2); 
private:
    T m_tReal, m_tImag; 
public:
    CComplex(); 
    CComplex(const T& real = 0, const T& imag = 0); 
    CComplex(const CComplex& com); 
    ~CComplex(); 

    T imag() const; 
    T real() const; 
    
    CComplex<T>& operator=(const T); 
    CComplex<T>& operator=(const CComplex<T>& com); 
    CComplex<T>& operator+=(const T); 
    CComplex<T>& operator+=(const CComplex<T>& com); 
    CComplex<T>& operator-=(const T); 
    CComplex<T>& operator-=(const CComplex<T>& com); 
    CComplex<T>& operator*=(const T); 
    CComplex<T>& operator*=(const CComplex<T>& com); 
    CComplex<T>& operator/=(const T); 
    CComplex<T>& operator/=(const CComplex<T>& com); 
}; 

template<typename T>
inline CComplex<T>::CComplex()
{
    m_tReal = m_tImage = 0; 
}

template<typename T>
inline CComplex<T>::CComplex(const T& real, const T& imag)
{
    m_tReal = real; 
    m_tImag = imag; 
}

template<typename T>
inline CComplex<T>::CComplex(const CComplex& com)
{
    m_tReal = com.m_tReal; 
    m_tImag = com.m_tImag; 
}

template<typename T>
inline CComplex<T>::~CComplex()
{
}

template<typename T>
inline T CComplex<T>::imag() const 
{
    return m_tImag; 
}

template<typename T>
inline T CComplex<T>::real() const
{
    return m_tReal; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator=(T val)
{
    m_tReal = val; 
    m_tImag = 0.0; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator+=(T val)
{
    m_tReal += val; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator-=(T val)
{
    m_tReal -= val; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator*=(T val)
{
    m_tImag *= val; 
    m_tReal *= val; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator/=(T val)
{
    m_tImag /= val; 
    m_tReal /= val; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator+=(const CComplex<T>& com)
{
    m_tReal += com.m_tReal; 
    m_tImag += com.m_tImag; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator-=(const CComplex<T>& com)
{
    m_tReal -= com.m_tReal; 
    m_tImag -= com.m_tImag; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator*=(const CComplex<T>& com)
{
    T tmp1(m_tReal), tmp2(m_tImag); 
    m_tReal = tmp1 * com.m_tReal - tmp2 * com.m_tImag; 
    m_tImag = tmp1 * com.m_tImag + tmp2 * com.m_tReal; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator/=(const CComplex<T>& com)
{
    T tmp1(m_tReal), tmp2(m_tImag); 
    T norm = abs(com); 
    m_tReal = (tmp1 * com.m_tReal + tmp2 * com.m_tImag) / norm; 
    m_tImag = (-tmp1 * com.m_tImag + tmp2 * com.m_tReal) / norm; 
    return *this; 
}


template< typename T>
inline T norm(const CComplex<T>& a)
{
    return a.real() * a.real() + a.imag() * a.imag(); 
}

template< typename T>
inline T abs(const CComplex<T>& a)
{
    return T(sqrt(norm(a))); 
}

template<typename T>
inline CComplex<T> conj(const CComplex<T>& a)
{
    return CComplex<T>(a.real(), -a.imag()); 
}

template< typename T>
inline CComplex<T> operator+(const CComplex<T>& com1, const CComplex<T>& com2)
{
    T real, imag; 
    real = com1.m_tReal + com2.m_tReal; 
    imag = com1.m_tImag + com2.m_tImag; 
    return CComplex<T>(real, imag); 
}

template<typename T>
inline CComplex<T> operator-(const CComplex<T>& com1, const CComplex<T>& com2)
{
    T a, b; 
    a = com1.real() - com2.real(); 
    b = com1.imag() - com2.imag(); 
    return CComplex<T>(a, b); 
}

template<typename T>
inline CComplex<T> operator*(const CComplex<T>& com1, const CComplex<T>& com2)
{
    T a, b; 
    a = com1.real() * com2.real() - com1.imag() * com2.imag(); 
    b = com1.real() * com2.imag() + com1.imag() * com2.real(); 
    return CComplex<T>(a, b); 
}

template<typename T>
inline CComplex<T> operator/(const CComplex<T>& com1, const CComplex<T>& com2)
{
    T a, b; 
    T norm = norm(com2); 
    a = (com1.real() * com2.real() + com1.imag() * com2.imag()) / norm; 
    b = (-com1.real() * com2.imag() + com1.imag() * com2.real()) / norm; 
    return CComplex<T>(a, b); 
}

template<typename T>
inline bool operator==(const CComplex<T>& com1, const CComplex<T>& com2)
{
    if((com1.real() == com2.real()) && (com1.imag() == com2.imag()))
        return true; 
    else 
        return false; 
}

template<typename T>
inline bool operator!=(const CComplex<T>& com1, const CComplex<T>& com2)
{
    if((com1.real() == com2.real()) && (com1.imag() == com2.imag()))
        return false; 
    else 
        return true; 
}

int main(int argc, char* argv[])
{
    CComplex<float> a(10, 10); 
    CComplex<float> b(2, 2); 
    CComplex<float> c = a + b; 
    CComplex<float> d(1); 

	return 0;
} 
