// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>

class X
{
public:
    bool GetFlag() const 
    {
        m_accessCount ++; 
        return m_flag; 
    }

private:
    bool m_flag; 
    mutable int m_accessCount; 
}; 

void Print(const char*){}
void Print(char*){}

//void Draw(const int){}
//void Draw(int){} 

void f(long a){}
void f(double a){} 

template<typename T>
T min(T a, T b)
{
    return a < b ? a : b; 
}

template<typename T>
T min(T a, T b, T c)
{
    T t = min(a, b); 
    return min(t, c); 
}

template<typename T>
T max(T a, T b)
{
    return a < b ? b : a; 
}

int max(int a, int b)
{
    return a < b ? b : a; 
}

char* max(char* a, char* b)
{
    return strcmp(a, b) > 0 ? a : b; 
}

template<typename T>
T h()
{
    T a; 
    return a; 
}

template<typename T>
void g()
{
    T a; 
}

template<typename T>
void q(T* p)
{
    static T t; 
}

int main(int argc, char* argv[])
{
    X x; 
    x.GetFlag(); 

    char* pch = new char(0x76); 
    delete pch; 

    pch = new char[10]; 
    delete[] pch; 

    //f(10); 
    f(10L); 
    f(10.0F); 

    min(1, 2, 3); 

    int i=0; 
    char c = 'a'; 
    float f = 1.0F; 
    max(i, i); 
    max(f, f); 
    //max(i, c); 

    char* sz1 = "ABCDEFG"; 
    char* sz2 = "ABCDEFH"; 
    max(sz1, sz2); 

    g<int>(); 
    h<char>(); 
    q(&i); 
    q(&c); 
    q(&f); 

    X* pX = new X; 
    pX->GetFlag(); 
    delete pX; 

    X& rX = * new X; 
    rX.GetFlag(); 
    delete &rX; 
	return 0;
}
