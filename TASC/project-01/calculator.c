#include <stdio.h>
#include <math.h>
#include "genlib.h"
#include "strlib.h"
#include "simpio.h"

#define MaxStackSize 100

typedef struct
{
    int arr[MaxStackSize];
    int top;
} *stack;


void hint(int mode)
{
    if (mode == 1)
        printf("Input expression is illegal!\n");
    else if (mode == 2)
        printf("Your expression has no answer in our mathematics.\n");
    else if (mode == 3)
        printf("No such function provided.\n");
}
int check(string line);
int priority(int opt);
string norm(string expr);
double sigcalc(double num, int opt)
{
    if (opt == 's') {
        return sin(num);
    }
    else if (opt == 'c') {
        return cos(num);
    }
}
int calc(stack nums, int opt, double* ans)
{
    if (size(nums) == 0)
        return 1;
    else if (issig(opt)) {
        double *num = (double*)top(nums);
        *ans = sigcalc(*num, opt);
    }
    else {
        double *rhs = (double*)pop(nums);
        if (size(nums) == 0) {
            return 1;
        }
        else {
            double *lhs = (double*)top(nums);
            *ans = bicalc(*lhs, *rhs, opt);
            push(nums, (void*)rhs);
        }
    }
    return 0;
}
int calcexpr(string expr, double* ans)
{
    stack nums, opts;
    nums = New(stack);
    opts = New(stack);
    int i;
    for (i = 0; i != StringLength(expr); ++i) {
        if (isnum(i)) {
            push(nums, getnum(i));
        }
        else if (isopt(i)) {
            int opt = getopt(i);
            if (priority(opt) < priority(top(opts))) {
                if (opt == ')') {
                    while (!ispar(top(opts) && !isfun(top(opts))) {
                        int subans = 0;
                        int flag = calc(nums, top(opts), &subans);
                        if (flag != 0) {
                            free(nums);
                            free(opts);
                            return flag;
                        }
                        else {
                            
                        }
                    }
                }
                else {

                }
            }
            else {
            push(opts, op)t;
            }
        }
    }

    free(nums);
    free(opts);
    return 0;
}
void process()
{
    
    string expr;
    
    printf("Please enter a legal arithmatic expression:\n");
    expr = GetLine();
    if (!check(expr))
        hint(1); //illegal input
    else {
        expr = norm(expr);
        int ans = 0;
        int flag = calcexpr(expr, &ans);
        hint(flag);
    }
}

int main()
{
    process();
    
    return 0;
    
}