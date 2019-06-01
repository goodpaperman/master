// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 
#include <math.h>
#include <typeinfo.h>
#include <conio.h> 

class B { virtual void g(){} }; 
class C : public B {}; 
class D : public C {}; 

void f(D* pd)
{
    C* pc = dynamic_cast<C*>(pd); 
    B* pb = dynamic_cast<B*>(pd); 
}

void f2()
{
    B* pb = new C; 
    B* pb2 = new B; 
    C* pc = dynamic_cast<C*>(pb); 
    C* pc2 = dynamic_cast<C*>(pb2); 
    delete pc; 
    delete pb2; 
}

class E : public B {}; 
class F : public B {}; 
class G : public E, public F {}; 

void f3()
{
    G* pg = new G; 
    //B* pb = dynamic_cast<B*>(pg); 
    E* pe = dynamic_cast<E*>(pg); 
    B* pb = dynamic_cast<B*>(pe); 
    delete pg; 
}

class K {}; 
class L : public K {}; 
class M : public K {}; 
class N { virtual void n(){} }; 
class P : public L, public M, public N {}; 

void f4(N* n)
{
    P* p = dynamic_cast<P*>(n); 
    L* l = dynamic_cast<L*>(p); 
    K* k = dynamic_cast<K*>(l); 
}

void f5(N* n)
{
    L* l = dynamic_cast<L*>(n); 
    K* k = l; 
}

class R { virtual void r(){} }; 
class S {}; 

void f6()
{
    R* r = new R; 
    S* s = dynamic_cast<S*>(r); 
    delete r; 
}

class T
{
public:
    virtual void function() = 0; 
}; 

void T::function()
{
    cout << "Pure virtual function is called." << endl; 
}

class W : public T
{
public:
    virtual void function(){} 
    void f() { T::function(); }
}; 

int main(int argc, char* argv[])
{
    D d; 
    f(&d); 

    f2(); 
    f3(); 

    P p; 
    f4(&p); 
    f5(&p); 

    f6(); 

    W w; 
    w.f(); 
	return 0;
} 
