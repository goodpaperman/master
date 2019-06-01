// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream.h> 
#include <math.h>

class TSample
{
public:
    TSample(float i); 
    friend TSample operator+(const TSample& x, const TSample& y); 
    operator float() const; 
private:
    float fValue; 
}; 

TSample::TSample(float i)
{
    fValue = i; 
}

TSample operator+(const TSample& x, const TSample& y)
{
    float f = x.fValue + y.fValue; 
    return f; 
}

TSample::operator float() const
{
    return fValue; 
}

class B; 
class A
{
public:
    A(){}
    A(B& b){}
    friend A operator+(const A& x, const A& y); 
}; 

class B
{
public:
    B(){}
    B(A& a){} 
    friend B operator+(const B& x, const B& y); 
}; 

A operator+(const A& x, const A& y)
{
    return x; 
}

B operator+(const B& x, const B& y)
{
    return y; 
}

int main(int argc, char* argv[])
{
    TSample Sample(1976.0630f); 
    Sample + (TSample)1972.0506f; 
    double f = Sample * 1972.0506f; 

    A a; 
    B b; 
    a = a + a; 
    b = b + b; 
    //a + b; 
	return 0;
} 
