// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 
#include <math.h>

class A
{
public:
    A(){}
    A(int i){}
}; 

class B : public A
{
public:
    B(){}
    B(int i) : A(i){}
}; 

class C
{
public:
    C() {}
    C(float f){}
}; 

class D : public C, public A
{
public:
    D(){}
    D(float i, int j) : A(j), C(i) {}
}; 

class E
{
public:
    E(){}
    E(const E& e){ m_e = e.m_e; }
    E& operator=(const E& e){ m_e = e.m_e; return *this; }

private:
    int m_e; 
}; 

class F
{
public:
    F(){}
    F(const F& f){ a = f.a; }
    F& operator=(const F& f){ a = f.a; return *this; }
private:
    E a; 
}; 

class G : E
{
public:
    G() : E(){}
    G(const G& g) : E(g){}
    G& operator=(const G& g){ E::operator=(g); return *this; } 
}; 

class TBase
{
public:
    int nData; 
}; 

class H : public TBase {}; 
class I : public TBase {}; 
class J : public H, public I {}; 

class K : public virtual TBase {}; 
class L : public virtual TBase {}; 
class M : public K, public L {}; 

class XBase
{
public:
    int nData; 
    XBase(int n) { nData = n; } 
}; 

class N : public virtual XBase
{
public:
    N(int n) : XBase(n) {}
}; 

class O : public virtual XBase 
{
public:
    O(int n) : XBase(n) {}
}; 

class P : public N, public O
{
public:
    P(int n) : N(n), O(n), XBase(n) {} 
}; 

int main(int argc, char* argv[])
{
    D d(1.2f, 2); 

    F f1; 
    F f2(f1); 
    f2 = f1; 

    G g1; 
    G g2(g1); 
    g2 = g1; 

    J j; 
    //j.nData = 0; 
    TBase* pBase; 
    //pBase = &j; 

    j.I::nData = 0; 
    j.H::nData = 1; 

    pBase = (I*)&j; 
    pBase = (H*)&j; 

    M m; 
    pBase = &m; 
    m.nData = 0; 

    P p(10); 
    XBase* pX = &p; 
    p.nData = 0; 
	return 0;
} 
