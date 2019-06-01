// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 

void func()
{
    //static int n; 
    class TInner
    {
    public:
        int n; 
        void Init(int i) { n = i; }
    }; 

    TInner Inner; 
    Inner.Init(100); 
}

class COuter
{
private:
    int m_nOutData; 
public:
//private:
    class CInner
    {
    private:
        int m_nInData;     
    public:
        CInner(){}
        void Operate(COuter* pOuter){}
    }; 

    void DoSomething() {}
}; 

class A
{
public:
    int func(int, double){ return 0; }
//private:
    int n; 
}; 

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

class CMember
{
public:
    int d; 
    //CMember(); 
    CMember(int j); 
}; 

//inline CMember::CMember()
//{
//    cout << "The default constructor called." << endl; 
//}

inline CMember::CMember(int j)
{
    d = j; 
    cout << "The constructor with one parameter called." << endl; 
}

class CContainer
{
private:
    CMember m; 
public:
    CContainer(); 
    CContainer(int j); 
}; 

inline CContainer::CContainer() : m(0)
{
    //m.d = 0;
}

inline CContainer::CContainer(int j) : m(j) 
{
    //m.d = j; 
}

class B
{
public:
    B(int j, int& k); 
private:
    const int a; 
    int& b; 
}; 

inline B::B(int j, int& k) : a(j), b(k)
{
}

int main(int argc, char* argv[])
{
    func(); 

    COuter outer; 
    COuter::CInner inner; 
    inner.Operate(&outer);    

    int A::*ptr; 
    int (A::*pfunc)(int, double); 
    ptr = &A::n; 
    pfunc = A::func; 

    A a; 
    a.*ptr = 100; 
    (a.*pfunc)(100, 5.3); 

    A* pA = &a; 
    pA->*ptr = 200; 
    (pA->*pfunc)(100, 6.3); 

    CComplex com(10.0f); 
    //CComplex com2(10.0f, 0.0f, 0.0f); 
    CComplex* pcom = new CComplex(10.f); 
    delete pcom; 

    CComplex com1; 
    CComplex com2(5.06f); 
    CComplex com3(10.013f, 5.05f); 
    CComplex com4(com3); 

    CComplex w = CComplex(2.02f); 
    CComplex x = CComplex(5.05f, 10.013f); 
    CComplex y = x; 

    CComplex r(2.02f); 
    CComplex s(5.05f, 10.013f); 
    CComplex t(s); 

    CContainer c(12); 

    int d = 12;     
    B b(12, d); 

    CComplex c1, c2, c3; 
    c1 = c2; 
    c1.operator=(c2); 
    c1 = c2 = c3; 
	return 0;
}
