#include <stdio.h>
#define MAXSIZE 200

int findpos(int *, int, int, int);
void move(int*, int, int);

int main()
{
    int A[MAXSIZE];
    int n, i, notsorted = 1;
    printf("Please enter the size of the integer array:\n");
    scanf("%d", &n);
    printf("Enter the integer array:\n");
    for (i = 0; i != n; ++i) {
        scanf("%d", &A[i]);
    }
    while (notsorted) {
        int p = -1;
        for (i = 1; i < n; ++i) {
            if (A[i] < A[i - 1]) {
                p = i;
                break;
            }
        }
        if (p == -1) {
            notsorted = 0;
        }
        else {
            move(A, p, findpos(A, 0, p - 1, A[p]));
        }
    }
    for (i = 0; i != n; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
int findpos(int *A, int l, int r, int x)
{
    int i;
    for (i = l; i <= r; ++i) {
        if (x < A[i])
            return i;
    }
}
void move(int *A, int a, int b) //move the ath number in A to position b
{
    int x = A[a];
    int i;
    if (a > b) {
        for (i = a; i > b; --i) {
            A[i] = A[i - 1];
        }
        A[b] = x;
    }
    else {
        for (i = a; i < b; ++i) {
            A[i] = A[i + 1];
        }
        A[b] = x;
    }
}