#include <stdio.h>
#include <stdbool.h>

#define MAX_STUDENTS 30
#define MAX_TESTS 10

int readIntInRange(const char *msg, int min, int max)
{
    int num;

    while (true)
    {
        printf("%s", msg);

        if (scanf("%d", &num) != 1)
        {
            // Clear invalid input (e.g., letters)
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (num >= min && num <= max)
            return num;

        printf("Out of range. Enter a value between %d and %d.\n", min, max);
    }
}

float studentAverage(int grades[MAX_STUDENTS][MAX_TESTS], int studentIndex, int M)
{
    int i;
    int sum = 0;

    for (i = 0; i < M; i++)
        sum += grades[studentIndex][i];

    return (float)sum / (float)M;
}

float testAverage(int grades[MAX_STUDENTS][MAX_TESTS], int testIndex, int N)
{
    int i;
    int sum = 0;

    for (i = 0; i < N; i++)
        sum += grades[i][testIndex];

    return (float)sum / (float)N;
}

int main(void)
{
    int N, M;
    int i, j;

    const char *msg1 = "Enter the number of students (1-30): ";
    const char *msg2 = "Enter the number of total tests (1-10): ";
    const char *msg3 = "Enter the grade (0-100): ";

    N = readIntInRange(msg1, 1, 30);
    M = readIntInRange(msg2, 1, 10);

    int grades[MAX_STUDENTS][MAX_TESTS];

    for (i = 0; i < N; i++)
    {
        printf("Scores for student %d\n", i + 1);
        for (j = 0; j < M; j++)
        {
            grades[i][j] = readIntInRange(msg3, 0, 100);
        }
    }

    // Student averages
    for (i = 0; i < N; i++)
    {
        printf("Student %d average: %.2f\n", i + 1, studentAverage(grades, i, M));
    }

    // Test averages
    for (i = 0; i < M; i++)
    {
        printf("Test %d average: %.2f\n", i + 1, testAverage(grades, i, N));
    }

    // Max and min (inside main, as you wanted)
    int maxG = grades[0][0];
    int minG = grades[0][0];

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (grades[i][j] > maxG) maxG = grades[i][j];
            if (grades[i][j] < minG) minG = grades[i][j];
        }
    }

    printf("Highest grade: %d\n", maxG);
    printf("Lowest grade: %d\n", minG);

    return 0;
}