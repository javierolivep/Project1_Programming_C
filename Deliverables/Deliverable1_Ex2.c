#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;         // Student ID
    float grade;    // Average grade
    int credits;    // Number of credits passed
} Student;

void Init(Student s[], int numStudents) {
    if (numStudents < 3) 
        return;

    s[0].id = 1111; s[0].grade = 6.5f; s[0].credits = 60;
    s[1].id = 1112; s[1].grade = 7.5f; s[1].credits = 30;
    s[2].id = 1113; s[2].grade = 9.0f; s[2].credits = 90;
}

float Average(Student s[], int numStudents) {
    if (numStudents <= 0) 
        return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < numStudents; i++) {
        sum += s[i].grade;
    }
    return sum / (float)numStudents;
}

int main(void) {
    int usedStudents = 3;

    Student *students = (Student *)malloc(usedStudents * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    Init(students, usedStudents);

    float avg = Average(students, usedStudents);
    printf("Average grade of all students: %.2f\n", avg);

    free(students);

    return 0;
}