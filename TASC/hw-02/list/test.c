#include <stdio.h>
#include "list.h"

int main()
{
    listADT s1, s2, s3;
    printf("Please enter a non-decreasing sequence of non-negative numbers which ends with -1.\n");
    s1 = GetList();
    printf("Please enter another non-decreasing sequence which also ends with -1.\n");
    s2 = GetList();
    printf("Combination of the two: \n");
    s3 = MergeList(s1, s2);
    PutList(s3);
    return 0;
    
}