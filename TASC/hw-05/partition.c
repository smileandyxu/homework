#include <stdio.h>

int ans[100];
int tot, x;

void par(int n, int k)
{
	if (n == 0) {
		int i;
		printf("%d = ", x);
		printf("%d", ans[0]);
		for (i = 1; i != tot; ++i) {
			printf("+%d", ans[i]);
		}
		printf("\n");
	}
    if (n > 0) {
        int i;
        for (i = k; i >= 1; --i) {
        	if (n >= i) {
        		ans[tot++] = i;
	            par(n - i, i);
	            --tot;
	        }
        }
    }
}

int main()
{
	scanf("%d", &x);
    par(x, x - 1);
    return 0;
}
