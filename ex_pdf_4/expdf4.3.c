#include <stdio.h>

int main(void)
{
    int N, i, j;
    int sum = 0;

    printf("Enter the number of operations 'N': ");
    scanf("%d", &N);

    for (i = 1; i <= N; i++)
    {
        sum += i;

        /* print: 1+2+...+i */
        for (j = 1; j <= i; j++)
        {
            if (j > 1) printf("+");
            printf("%d", j);
        }

        printf("=%d\n", sum);
    }

    return 0;
}