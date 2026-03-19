#include <stdio.h>
#include <stdlib.h>

float CustomerCalc(char cat, float price)
{
    if (cat == 'B')
    {
        return price;
    }
    else if (cat == 'S')
    {
        if (price > 10000.0)
            return (price * 0.95);
        else
            return price;
    }
    else
    {
        if (price <= 100.0)
            return price;
        else if ((price > 100.0) && (price <= 1000.0))
            return (price * 0.95);
        else if ((price > 1000.0) && (price <= 10000.0))
            return (price * 0.9);
        else
            return (price * 0.8);
    }
}

int main(void)
{
    char cat;
    float price, result;

    printf("Enter the catergory ('B'/'S'/'P'): ");
    scanf("%c", &cat);

    if (!((cat == 'B') || (cat == 'S') || (cat == 'P')))
    {
        printf("ERROR: category is not correct!");
        exit(0); 
    }

    printf("\nEnter the purchase amount: ");
    scanf("%f", &price);

    result = CustomerCalc(cat, price);
    printf("\nThe final amount to be paid is: %.2f", result);
    return 0;

}