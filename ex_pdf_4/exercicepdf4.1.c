#include <stdio.h>
#include <stdlib.h>

void Sort3(int *a, int *b, int *c)
{
    int temp;

    // Si a > b, intercambiamos a y b
    if (*a > *b) {
        temp = *a;
        *a = *b;
        *b = temp;
    }

    // Si a > c, intercambiamos a y c
    if (*a > *c) {
        temp = *a;
        *a = *c;
        *c = temp;
    }

    // Si b > c, intercambiamos b y c
    if (*b > *c) {
        temp = *b;
        *b = *c;
        *c = temp;
    }
}

int main(void)
{
    int x, y, z;

    printf("Enter three integers: ");
    scanf("%d %d %d", &x, &y, &z);

    Sort3(&x, &y, &z);

    printf("Sorted: %d %d %d\n", x, y, z);

    return 0;
}