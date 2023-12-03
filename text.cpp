#include <iostream>
using namespace std;
struct A
{
    A() { cout << 'A'; }
};
struct B
{
    const A a;
    B() { cout << 'B'; }
};
struct C
{
    C() { cout << 'C'; }
};
struct D
{
    D() { cout << 'D'; }
};
struct E : A
{
    E() { cout << 'E'; }
};
struct F : B, virtual C
{
    F()
    {
        cout << 'F';
    }
};
struct G : B
{
    G() { cout << 'G'; }
};
struct H : virtual C, virtual D
{
    H()
    {
        cout << 'H';
    }
};
struct I : E, F, virtual G, H
{
    E e;
    F f;
    I() : f(), e(), F(), E() { cout << 'I'; }
};
int main(void) { I i; }