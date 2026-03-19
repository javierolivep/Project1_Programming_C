#include <stdio.h>

void Fibonacci(int N)
{
    int F;
    int a = 0;   // F(0)
    int b = 1;   // F(1)
    int next;    // F(n)

    if (N >= 0) 
        printf("F(0)=%d\n", a);
    if (N >= 1) 
        printf("F(1)=%d\n", b);

    for (F = 2; F <= N; F++)
    {
        next = a + b;          // F(n)=F(n-2)+F(n-1)
        printf("F(%d)=%d\n", F, next);
        a = b;                 
        b = next;
    }
}

int main(void)
{
    int N;

    printf("Enter 'N' for the first numbers of the Fibonacci sequence: ");
    scanf("%d", &N);
    Fibonacci(N);
    return 0;
}