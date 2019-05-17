#include "circle.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int scan_errors(Circle* c, char* str, int index)
{
    char circle[7] = "circle\0";
    for (int i = 0; circle[i] != '\0'; i++) {
        if (circle[i] != str[i]) {
            return 1;
        }
    }
    // Массивы для x, y, r
    char* temp_x = (char*)malloc(sizeof(char) * MAX);
    char* temp_y = (char*)malloc(sizeof(char) * MAX);
    char* temp_r = (char*)malloc(sizeof(char) * MAX);

    for (int i = 0; i < MAX; i++) {
        temp_x[i] = 0;
        temp_y[i] = 0;
        temp_r[i] = 0;
    }

    // Пробелы перед скобкой
    int i = 6;
    while (isspace(str[i]) != 0) {
        i++;
    }
    // Наличие скобки
    if (str[i] != '(') {
        return 2;
    }
    // Следующий символ в строке
    i++;
    // Пробелы перед x
    while (isspace(str[i]) != 0) {
        i++;
    }

    for (int j = 0; str[i] != ' '; i++, j++) {
        // Синтаксис x
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != '-') {
            return 4;
        }
        temp_x[j] = str[i];
    }

    (c + index)->x = atof(temp_x);
    // Пробелы перед y
    while (isspace(str[i]) != 0) {
        i++;
    }

    for (int j = 0; str[i] != ','; i++, j++) {
        // Синтаксис y
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != '-') {
            return 4;
        }
        temp_y[j] = str[i];
    }
    (c + index)->y = atof(temp_y);
    // Следующий символ в строке
    i++;
    // Пробелы перед r
    while (isspace(str[i]) != 0) {
        i++;
    }
    // Знак r
    if (str[i] == '-') {
        return 5;
    }

    for (int j = 0; str[i] != ')' && str[i] != ' '; i++, j++) {
        if (str[i] == '\0' || str[i] == '\n') {
            return 2;
        }
        // Синтаксис r
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
            return 4;
        }
        temp_r[j] = str[i];
    }
    (c + index)->r = atof(temp_r);

    while (isspace(str[i]) != 0) {
        i++;
    }
    // Наличие скобки
    if (str[i] != ')') {
        return 2;
    }
    i++;
    while (isspace(str[i]) != 0) {
        i++;
    }

    if (str[i] != '\0' && str[i] != '\n') {
        return 3;
    }
    free(temp_x);
    free(temp_y);
    free(temp_r);
    return 0;
}

void print_circle(Circle* c, int size)
{
    int intersect;
    for (int i = 1; i < size; i++) {
        printf("%d. circle(%f %f, %f)\n",
               (c + i)->index,
               (c + i)->x,
               (c + i)->y,
               (c + i)->r);
        printf("\tperimeter = %f\n", get_perimeter(c, i));
        printf("\tarea = %f\n", get_area(c, i));
        printf("\tintersects: \n");
        for (int j = 1; j < size; j++) {
            if (i == j) {
                continue;
            }
            intersect = get_intersect(c, i, j);
            if (intersect) {
                printf("\t\t%d. circle\n", (c + j)->index);
            }
        }
    }
}

double get_perimeter(Circle* c, int i)
{
    return (c + i)->r * 2 * M_PI;
}

double get_area(Circle* c, int i)
{
    return (c + i)->r * (c + i)->r * M_PI;
}

int get_intersect(Circle* c, int i, int j)
{
    double dis;
    dis
            = sqrt((double)pow((c + i)->x - (c + j)->x, 2.00)
                   + (double)pow((c + i)->y - (c + j)->y, 2.00));
    if (dis < (c + i)->r + (c + j)->r && (c + i)->r < dis + (c + j)->r
        && (c + j)->r < dis + (c + i)->r) {
        return 1;
    }
    return 0;
}

void print_error(int error_numb, int index, int count_err)
{
    switch (error_numb) {
    case 1:
        printf("String %d\n\t error: ", index + count_err);
        printf("Name Error\n");
        break;
    case 2:
        printf("String %d\n\t error: ", index + count_err);
        printf("Missing Bracket\n");
        break;
    case 3:
        printf("String %d\n\t error: ", index + count_err);
        printf("Syntax End File Error\n");
        break;
    case 4:
        printf("String %d\n\t error: ", index + count_err);
        printf("Coordinate Error\n");
        break;
    case 5:
        printf("String %d\n\t error: ", index + count_err);
        printf("Radius can`t be < 0\n");
        break;
    }
}
