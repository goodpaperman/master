// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 
#include <math.h>

class A
{
    friend class B; 
private:
    int a; 
}; 

class B : public A
{
    void fun(){ a = 1; }
}; 

class C : public B
{
    void f() 
    { 
        //a = 0; 
    }
}; 

class D
{
protected:
    int p; 
}; 

class E : public D
{
    void fun() { p = 0; }
}; 

class F
{
public:
    void f();
}; 

class G : private F
{
public:
    void g(){ f(); }
}; 

class H : public G
{
public:
    void h() 
    {
        g(); 
        //f(); 
    }
}; 

class I
{
public:
    static void i() {} 
}; 

class J : private I
{
}; 

class K : public J
{
public:
    void k(K* p); 
}; 

void K::k(K* p)
{
    I::i(); 
    //i(); 
    //p->i(); 
}

class L
{
}; 

class M : private L
{
    friend void m(M* p); 
public:
    L* n(); 
}; 

void m(M* p)
{
    L* pl = static_cast<L*>(p); 
}

L* M::n()
{
    M* p = new M; 
    return p; 
}

class N
{
public:
    int a() { return c; } 
protected:
    int c; 
private:
    int b; 
}; 

class O : private N
{
public:
    N::a; 
protected:
    N::c; 
}; 

class P
{
public:
    void f(){} 
    int f(int){return 0; } 
}; 

class Q : private P
{
public:
    P::f; 
}; 

class R
{
public:
    void f(int); 
private:
    void f(); 
}; 

class S : private R
{
public:
    //R::f; 
}; 

class T : private P
{
public:
    int f(){return 1; } 
    P::f; 
}; 

class U
{
public:
    void f(){}
}; 

class V : public U
{
public:
    void f(){}
    void g(); 
}; 

void V::g()
{
    f(); 
    U::f(); 
}

class W 
{
public:
    int f(){return 1; }
}; 

class X 
{
public:
    int f(){return 0; }
}; 

class Y : public W, private X
{
public:
    int g(); 
}; 

int Y::g()
{
    //f(); 
    X::f(); 
    return W::f(); 
}

int main(int argc, char* argv[])
{
    //E e; 
    //e.p = 0; 

    //G g; 
    //g.f(); 

    //H h; 
    //h.f(); 

    N n; 
    n.a(); 

    Q q; 
    q.f(); 
    q.f(1); 
     
    T t; 
    t.f(); 

    V v; 
    v.f(); 
    v.g(); 
    v.U::f(); 
	return 0;
}
