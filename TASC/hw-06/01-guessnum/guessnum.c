#include <stdio.h>
#include <strlib.h>

int main()
{
    int lb = 1, rb = 100;
    int notfound = 1;
    printf("Tink of a number between 1 and 100 and I'll guess it.\n");
    printf("NOTICE: Please enter in lower case characters!\n");
    while (lb <= rb && notfound) {
        char inputstr[10];
        int d = (lb + rb) >> 1;
        printf("Is it %d?\n", d);
        while (scanf("%s", inputstr)) {
            if (StringEqual(inputstr, "yes")) {
                printf("I guessed the number!\n");
                notfound = 0;
                break;
            }
            else if (StringEqual(inputstr, "no")) {
                printf("Is it less than %d?\n", d);
                while (scanf("%s", inputstr)) {
                    if (StringEqual(inputstr, "yes")) {
                        rb = d - 1;
                        break;
                    }
                    else {
                        lb = d + 1;
                        break;
                    }
                }
                break;
            }
        }
    }
    return 0;
}