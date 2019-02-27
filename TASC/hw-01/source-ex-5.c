#include <stdio.h>
#include "rational.h"

int main()
{
    printf("This program adds a list of rational numbers.\nSignal end of list with a 0.\n");
    rationalT sum, tmp;
    sum = CreateRational(0, 1);
    tmp = CreateRational(0, 1);
    while (GetRational(&tmp)) {
        sum = AddRational(sum, tmp);
    }
    printf("The total is ");
    PrintRational(sum);
    return 0;
}