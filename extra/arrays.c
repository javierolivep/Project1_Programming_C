#include <stdio.h>
#include <stdlib.h>

#define N 100

void InitArray(float vect[N])
{
    int i;
    for (i = 0; i < N; i++)
        vect[i] = (rand() % 100) / 100.0f;   // 0.00 to 0.99
}

/* Returns max, and writes the sum into *sum */
float MaxAndSumArray(const float v[N], float *sum)
{
    int i;
    float max = v[0];
    float totalsum = v[0];

    for (i = 1; i < N; i++)
    {
        if (v[i] > max)
            max = v[i];

        totalsum += v[i];
    }

    *sum = totalsum;
    return max;
}

/* res[i] = op1[i] + op2[i] */
void AddVectors(const float op1[N], const float op2[N], float res[N])
{
    int i;
    for (i = 0; i < N; i++)
        res[i] = op1[i] + op2[i];
}

/* Print first 5 elements */
void PrintArray(const float v[N])
{
    int i;
    for (i = 0; i < 5; i++)
        printf("%d: %.2f\n", i + 1, v[i]);
}

int main(void)
{
    float v1[N], v2[N], v3[N];
    float max_v1, max_v2, total_v1, total_v2;

    srand(1234);

    InitArray(v1);
    InitArray(v2);

    max_v1 = MaxAndSumArray(v1, &total_v1);
    max_v2 = MaxAndSumArray(v2, &total_v2);

    printf("the maximum value of v1 is: %.2f and its total sum is: %.2f\n", max_v1, total_v1);
    printf("the maximum value of v2 is: %.2f and its total sum is: %.2f\n", max_v2, total_v2);

    AddVectors(v1, v2, v3);   // store v1+v2 into v3
    printf("First 5 values of v3 (v1 + v2):\n");
    PrintArray(v3);

    return 0;
}
