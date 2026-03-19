#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n1=3, n2=10;
    int *pn1, *pn2;
    pn1 = pn2 = NULL;

    pn1 = &n1; 
    pn2 = &n2;

    printf("The content of pn1 is: %d \n", *pn1);
    printf("The content of pn2 is: %d \n", *pn2);

    char name[] = "javi";
    printf("hello %s", name);
    return 0;
}