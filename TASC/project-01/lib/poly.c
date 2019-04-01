#include <stdio.h>
#include "genlib.h"
#include "poly.h"

const double inf = 1e20;
const double eps = 1e-5;
double myabs(double x)
{
    return (x > 0 ? x : -x);
}
bool DoubleEqual(double x, double y)
{
    return myabs(x - y) < eps;
}

struct term
{
    double coefficient, exponent;
    poly bck, nxt;
};

void swap(poly *A, poly *B)
{
	poly tmp = *A;
	*A = *B;
	*B = tmp;
	return;
}
int listlen(poly list)
{
    int cnt = 0;
    while (list) {
        cnt++;
        list = list->nxt;
    }
    return cnt;
}
poly addlist(poly list, double coefficient, double exponent) //'list' is the head of the linklist
{
    poly new_term = New(poly);
    new_term->nxt = list;
    new_term->bck = NULL;
    new_term->coefficient = coefficient;
    new_term->exponent = exponent;
    if (list != NULL)
        list->bck = new_term;
    return new_term;
}
void dellist(poly p)
{
    if (p == NULL)
        return;
    if (p->bck) {
        p->bck->nxt = p->nxt;
    }
    if (p->nxt) {
        p->nxt->bck = p->bck;
    }
    FreeBlock(p);
}
poly copylist(poly list)
{
    poly tmp = NULL;
    while (list) {
        tmp = addlist(tmp, list->coefficient, list->exponent);
        list = list->nxt;
    }
    return tmp;
}

poly findterm(poly list, double exp)
{
    poly ans = NULL;
    while (list) {
        if (DoubleEqual(list->exponent, exp)) {
            ans = list;
        }
        list = list->nxt;
    }
    return ans;
}
poly clean(poly list)
{
    while (list && DoubleEqual(list->coefficient, 0)) {
        poly p = list;
        list = list->nxt;
        dellist(p);
    }
    poly q = NULL;
    for (poly p = list; p; p = p->nxt) {
        dellist(q);
        if (DoubleEqual(p->coefficient, 0)) {
            q = p;
        }
        else {
            q = NULL;
        }
        
    }
    dellist(q);
    return list;
}
void freepoly(poly A)
{
	poly p=A,q;
	if(p!=NULL)
	{
		q=p->nxt;
		FreeBlock(p);
		p=q;
	}
	return;
}

poly plus(poly lhs, poly rhs)
{
    poly ans = copylist(lhs);
    while (rhs) {
        poly p = findterm(ans, rhs->exponent);
        if (p == NULL) {
            ans = addlist(ans, rhs->coefficient, rhs->exponent);
        }
        else {
            p->coefficient += rhs->coefficient;
        }
        rhs = rhs->nxt;
    }
    ans = clean(ans);
    return ans;
}
poly minus(poly lhs, poly rhs)
{
    poly tmp = copylist(rhs);
    for (poly p = tmp; p; p = p->nxt) {
        p->coefficient = -(p->coefficient);
    }
    poly ans = plus(lhs, tmp);
    freepoly(tmp);
    return ans;
}
poly multiply(poly lhs, poly rhs)
{
    poly ans = NULL;
    for (poly p = lhs; p; p = p->nxt) {
        for (poly q = rhs; q; q = q->nxt) {
            poly t = findterm(ans, p->exponent + q->exponent);
            if (t == NULL) {
                ans = addlist(ans, p->coefficient * q->coefficient, p->exponent + q->exponent);
            }
            else {
                t->coefficient += (p->coefficient * q->coefficient);
            }
        }
    }
    ans = clean(ans);
    return ans;
}

poly sort(poly A) //WARNING: THIS WILL DESTROY FORMER POLYNOMIAL!!!
{
    poly list = NULL;
    double mine = -inf;
    int n = listlen(A), i;
    for (i = 0; i != n; ++i) {
        poly minp = A;
        while (minp->exponent <= mine)
            minp = minp->nxt;
        for (poly p = A; p; p = p->nxt) {
            if (p->exponent < minp->exponent && p->exponent > mine) {
                minp = p;
            }
        }
        list = addlist(list, minp->coefficient, minp->exponent);
        mine = minp->exponent;
    }
	/*poly list=NULL,last=NULL,p,head=A,max;
	int n=listlen(A),i,j;
	for(i=1;i<=n;i++)
	{
		max=head;
		p=head->nxt;
		while(p!=NULL)
		{
			if(max->exponent<p->exponent) max=p;
			p=p->nxt;
		}
		if(max==head) head=head->nxt;
		if(list==NULL)
			list=last=init(max->coefficient,max->exponent,NULL);
		else{
			last->nxt=init(max->coefficient,max->exponent,last);
			last=last->nxt;
		}
		if(max->nxt!=NULL) max->nxt->bck=max->bck;
		if(max->bck!=NULL) max->bck->nxt=max->nxt;
	}*/
    freepoly(A);
	return list;
}

poly getpoly()/**/
{
    poly p = NULL;
    double x, y;
    while (scanf("%lf%lf", &x, &y) && x != 0 && y != 0) {
        p = addlist(p, x, y);
    }
    return clean(p);
}
void putpoly(poly A)
{
    A = sort(A);
    if (A == NULL)
        printf("0");
    else {
        while (A) {
            printf("%gx^%g", A->coefficient, A->exponent);
            A = A->nxt;
            if (A)
                printf("+");
        }
    }
    printf("\n");
}