#include <stdio.h>
#include "poly.h"

int main()
{
    poly A = getpoly();
    poly B = getpoly();
    putpoly(A);
    putpoly(B);
    putpoly(plus(A, B));
    putpoly(minus(A, B));
    putpoly(multiply(A, B));
    return 0;
}
/*
1 2
1 3
1 1
0 0
1 2
-1 3
0 0
*/