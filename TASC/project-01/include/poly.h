#ifndef _poly_h
#define _poly_h

typedef struct term* poly;

poly plus(poly, poly);
poly minus(poly, poly);
poly multiply(poly, poly);
poly getpoly();
void putpoly();
void freepoly(poly);
void swap(poly *A, poly *B);

#endif