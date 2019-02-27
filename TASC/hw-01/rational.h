#ifndef  _rational_h
#define _rational_h

#include <stdio.h>
#include <ctype.h>

//Interface Types
typedef struct {
    int num, den;
    int isnul;
} rationalT;

//Interface Functions
rationalT CreateRational(int, int);
rationalT AddRational(rationalT, rationalT);
rationalT MultiplyRational(rationalT, rationalT);
int GetRational(rationalT *);
void PrintRational(rationalT);

//Auxiliary Functions
int abs(int);
int gcd(int, int);
int sign(rationalT);
void simp(rationalT *); //simplify the common divisor
rationalT BiOpRational(rationalT, rationalT); //uncomplete higher abstraction


//Implementation
rationalT CreateRational(int _num, int _den)
{
    rationalT r;
    r.num = _num;
    r.den = _den;
    r.isnul = (_den == 0);
    return r;
}
rationalT AddRational(rationalT lhs, rationalT rhs)
{
    rationalT ans;
    ans.isnul = lhs.isnul || rhs.isnul;
    ans.num = lhs.num * rhs.den + lhs.den * rhs.num;
    ans.den = lhs.den * rhs.den;
    simp(&ans);
    return ans;
}
rationalT MultiplyRational(rationalT lhs, rationalT rhs)
{
    rationalT ans;
    ans.isnul = lhs.isnul | rhs.isnul;
    ans.num = lhs.num * rhs.num;
    ans.den = lhs.den * rhs.den;
    simp(&ans);
    return ans;
}
int GetRational(rationalT *r)
{
    int sig = 1; //sign
    char c = getchar();
    while (!isdigit(c) && c != '-')
        c = getchar();
    if (c == '-') {
        sig = -1;
        c = getchar();
    }
    if (!isdigit(c))
        r->isnul = 1;
    r->num = 0;
    while (isdigit(c)) {
        r->num = (r->num) * 10 + c - '0';
        c = getchar();
    }
    if (c != '/') {
        r->isnul = 1;
    }
    else {
        c = getchar();
        if (!isdigit(c)) {
            r->isnul = 1;
        }
        else {
            r->den = 0;
            while (isdigit(c)) {
                r->den = (r->den) * 10 + c - '0';
                c = getchar();
            }
        }
    }
    r->num *= sig;
    if (r->den == 0)
        r->isnul = 1;
    return r->isnul == 0;
}
void PrintRational(rationalT r)
{
    if (r.isnul) {
        printf("#NULL");
    }
    else {
        if (!sign(r))
            printf("-");
        printf("%d/%d", abs(r.num), abs(r.den));
    }
}

int abs(int x)
{
    return (x > 0 ? x : -x);
}
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int sign(rationalT x)
{
    return (x.num  * x.den >= 0);
}
void simp(rationalT *x)
{
    if (!(x->isnul) && x->num && x->den) {
        int comd = gcd(abs(x->num), abs(x->den));
        x->num /= comd;
        x->den /= comd;
    }
}

#endif