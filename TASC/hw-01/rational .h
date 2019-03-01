#ifndef  _rational_h
#define _rational_h

#include <stdio.h>
#include <ctype.h>

//Interface Types
typedef struct {
    int num, den;
} rationalT;

//Interface Functions
rationalT CreateRational(int, int);
rationalT AddRational(rationalT, rationalT);
rationalT MultiplyRational(rationalT, rationalT);
int GetRational(rationalT *);
void PrintRational(rationalT);

//Auxiliary Functions
int abs(int); //absolute function
int gcd(int, int); //greatest common divisor
int sign(rationalT); //the sign function of rational number
int isnul(rationalT); //decide whether this is a legal rational number
void simp(rationalT *); //simplify the common divisor of num and den

//Implementation
rationalT CreateRational(int _num, int _den)
{
    rationalT r;
    r.num = _num;
    r.den = _den;
    return r;
}
rationalT AddRational(rationalT lhs, rationalT rhs)
{
    rationalT ans;
    ans.num = lhs.num * rhs.den + lhs.den * rhs.num;
    ans.den = lhs.den * rhs.den;
    simp(&ans);
    return ans;
}
rationalT MultiplyRational(rationalT lhs, rationalT rhs)
{
    rationalT ans;
    ans.num = lhs.num * rhs.num;
    ans.den = lhs.den * rhs.den;
    simp(&ans);
    return ans;
}
int GetRational(rationalT *r)
{
    int sig = 1, flag = 1; //flag: decide the process work correctly
    char c = getchar();
    while (!isdigit(c) && c != '-')
        c = getchar();
    if (c == '-') {
        sig = -1;
        c = getchar();
    }
    if (!isdigit(c))
        flag = 0;
    r->num = 0;
    while (isdigit(c)) {
        r->num = (r->num) * 10 + c - '0';
        c = getchar();
    }
    if (c != '/') {
        flag = 0;
    }
    else {
        c = getchar();
        if (!isdigit(c)) {
            flag = 0;
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
    return (r->den != 0) && flag;
}
void PrintRational(rationalT r)
{
    if (isnul(r)) {
        printf("#NULL");
    }
    else if (r.num == 0) {
        printf("0");
    }
    else if (abs(r.den) == 1) {
        printf("%d", sign(r) * abs(r.num));
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
int isnul(rationalT x)
{
    return x.den == 0;
}
void simp(rationalT *x)
{
    if (!(isnul(*x)) && x->num && x->den) {
        int comd = gcd(abs(x->num), abs(x->den));
        x->num /= comd;
        x->den /= comd;
    }
}

#endif
