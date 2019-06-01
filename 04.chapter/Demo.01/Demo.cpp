// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 
#include <math.h>
#include <typeinfo.h>
#include <conio.h> 

class A
{
public:
    virtual void f(){}
    virtual void g(int n){}
    virtual void h(float x){}
    void function(float x); 
private:
    int nDataA; 
}; 

void A::function(float x)
{
    h(x); 
    A::h(x); 
}

class C : public A
{
public:
    virtual void h(float x){}
private:
    int nDataC; 
};

class D {}; 
class E : public D {}; 

class F
{
public:
    virtual void f() {}
}; 

class G : public F
{
public:
    virtual void f() {} 
}; 

int main(int argc, char* argv[])
{
    C c; 
    c.function(5.30f); 

    char C; 
    float X; 
    if(typeid(C) == typeid(X))
        cout << "C and X are the same type." << endl; 
    else 
        cout << "C and X are NOT the same type." << endl; 

    cout << typeid(int).name(); 
    cout << " before " << typeid(double).name() << " : " << 
        (typeid(int).before(typeid(double)) ? true : false) << endl; 
    cout << typeid(D).name(); 
    cout << " before " << typeid(E).name() << " : " << 
        (typeid(D).before(typeid(E)) ? true : false) << endl; 

    F* pa = new G(); 
    try
    {
        cout << "Name is " << typeid(*pa).name() << endl; 
    }
    catch(bad_typeid)
    {
        cout << "typeid has failed." << endl << endl; 
    }

    delete pa; 
	return 0;
} 
