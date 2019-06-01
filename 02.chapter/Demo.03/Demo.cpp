// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 
#include <math.h>

template<typename T>
class CComplex
{
    friend CComplex<T> operator+(const CComplex<T>& com1, const CComplex<T>& com2); 
    friend T norm(const CComplex<T>& a); 
    friend T abs(const CComplex<T> & a); 
    friend CComplex<T> conj(const CComplex<T>& a); 
private:
    T m_fltReal, m_fltImag; 
public:
    CComplex(const T& real_arg = 0, const T& imag_arg = 0); 
    CComplex(const CComplex& com); 
    ~CComplex(); 

    T imag() const; 
    T real() const; 
    
    CComplex<T>& operator=(T); 
    CComplex<T>& operator+=(T); 
    CComplex<T>& operator-=(T); 
    CComplex<T>& operator*=(T); 
    CComplex<T>& operator/=(T); 
}; 

template<typename T>
inline CComplex<T>::CComplex(const T& real_arg, const T& imag_arg)
{
    m_fltReal = real_arg; 
    m_fltImag = imag_arg; 
}

template<typename T>
inline CComplex<T>::CComplex(const CComplex& com)
{
    m_fltReal = com.m_fltReal; 
    m_fltImag = com.m_fltImag; 
}

template<typename T>
inline CComplex<T>::~CComplex()
{
}

template<typename T>
inline T CComplex<T>::imag() const 
{
    return m_fltImag; 
}

template<typename T>
inline T CComplex<T>::real() const
{
    return m_fltReal; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator=(T rhs)
{
    m_fltReal = rhs; 
    m_fltImag = 0.0; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator+=(T rhs)
{
    m_fltReal += rhs; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator-=(T rhs)
{
    m_fltReal -= rhs; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator*=(T rhs)
{
    m_fltImag *= rhs; 
    m_fltReal *= rhs; 
    return *this; 
}

template<typename T>
inline CComplex<T>& CComplex<T>::operator/=(T rhs)
{
    m_fltImag /= rhs; 
    m_fltReal /= rhs; 
    return *this; 
}

template< typename T>
CComplex<T> operator+(const CComplex<T>& com1, const CComplex<T>& com2)
{
    T real, imag; 
    real = com1.m_fltReal + com2.m_fltReal; 
    imag = com1.m_fltImag + com2.m_fltImag; 
    return CComplex<T>(real, imag); 
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
CComplex<T> conj(const CComplex<T>& a)
{
    return CComplex<T>(a.real(), -a.imag()); 
}

template<typename T1, typename T2>
class A
{
}; 

template<typename T1, int>
class B
{
}; 

void func(CComplex<float>& com)
{
}

template< typename T>
void f(CComplex<T>& com)
{
}

int main(int argc, char* argv[])
{
    CComplex<float> com; 
    func(com); 
    f(com); 

    norm(com); 
    abs(com); 
    conj(com); 
    CComplex<double> com1, com2, com3; 
    com1 = com2 + com3; 
	return 0;
}
