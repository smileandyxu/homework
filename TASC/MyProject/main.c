#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "simpio.h"

main() 
{
	int n;
	
	printf("Enter num: ");
	n = GetInteger();
	printf("Hello, %d!\n", n);
}
