// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 

class A
{
private:
    int *pn; 
public:
    A(int i); 
    A(const A& a); 
    A& operator=(const A& a);
    void Output(); 
    ~A(); 
}; 

A::A(int i)
{
    pn = new int; 
    *pn = i; 
}

A::A(const A& a)
{
    pn = new int; 
    *pn = *a.pn; 
}

A& A::operator=(const A& a)
{
    *pn = *a.pn; 
    return *this; 
}

void A::Output()
{
    cout << *pn << endl; 
}

A::~A()
{
    delete pn; 
}

class CComplex
{
private:
    float m_fltReal, m_fltImag; 
public:
    CComplex(const float& real_arg = 0, const float& imag_arg = 0); 
    CComplex(const CComplex& com); 
    ~CComplex(); 

    float imag() const; 
    float real() const; 
    
    CComplex& operator=(float); 
    CComplex& operator+=(float); 
    CComplex& operator-=(float); 
    CComplex& operator*=(float); 
    CComplex& operator/=(float); 
}; 

inline CComplex::CComplex(const float& real_arg, const float& imag_arg)
{
    m_fltReal = real_arg; 
    m_fltImag = imag_arg; 
}

inline CComplex::CComplex(const CComplex& com)
{
    m_fltReal = com.m_fltReal; 
    m_fltImag = com.m_fltImag; 
}

inline CComplex::~CComplex()
{
}

inline float CComplex::imag() const 
{
    return m_fltImag; 
}

inline float CComplex::real() const
{
    return m_fltReal; 
}

inline CComplex& CComplex::operator=(float rhs)
{
    m_fltReal = rhs; 
    m_fltImag = 0.0; 
    return *this; 
}

inline CComplex& CComplex::operator+=(float rhs)
{
    m_fltReal += rhs; 
    return *this; 
}

inline CComplex& CComplex::operator-=(float rhs)
{
    m_fltReal -= rhs; 
    return *this; 
}

inline CComplex& CComplex::operator*=(float rhs)
{
    m_fltImag *= rhs; 
    m_fltReal *= rhs; 
    return *this; 
}

inline CComplex& CComplex::operator/=(float rhs)
{
    m_fltImag /= rhs; 
    m_fltReal /= rhs; 
    return *this; 
}

void func(const CComplex& s)
{
    float a = s.real(); 
    //s += 3.0f; 
}

class B
{
private:
    static const int size; 
}; 

const int B::size = 10; 

class C
{
private:
    int nData; 
public:
    C(int i)
    {
        nData = i; 
    }

    C& operator=(const C& c)
    {
        nData = c.nData; 
        return *this;
    }

    C& operator=(const int i)
    {
        nData = i; 
        return *this; 
    }

    operator int()
    {
        return int(nData); 
    }

    void Output()
    {
        cout << nData << endl; 
    }
}; 

int main(int argc, char* argv[])
{
    A a(100); 
    a.Output(); 
    A b(a); 
    b.Output(); 

    A c(100), d(200); 
    c = d; 
    c.Output(); 
    c.Output(); 

    CComplex com; 
    func(com); 

    CComplex coms[2]; 
    CComplex comses[2] = 
    {
        CComplex(100, 100),
        CComplex(200, 200),
    }; 

    CComplex comseses[2] = 
    {
        CComplex(100, 100), 
    }; 

    CComplex* pcom = new CComplex[3]; 
    delete[] pcom; 

    C x(100); 
    x.Output(); 
    x = 1000; 
    x.Output(); 
    int n = 10; 
    n += x; 

    pcom = new CComplex(); 
    pcom->~CComplex(); 
    delete (void*)pcom; 
	return 0;
}
