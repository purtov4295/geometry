#include "circle.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file;
    file = fopen("./input/c.txt", "r");
    if (!file) {
        printf("Can`t open file\n");
        return -1;
    }
    char str[MAX];
    Circle* c = (Circle*)malloc(sizeof(Circle) * MAX);
    int i = 0;
    int count_err = 0;
    int check_ret;
    while (!feof(file)) {
        fgets(str, MAX, file);
        // if (strcmp(str, "\n\0") == 0) {
        //     continue;
        // }
        i++;
        (c + i)->index = i;
        check_ret = scan_errors(c, str, i);
        if (check_ret == 1 || check_ret == 2 || check_ret == 3 || check_ret == 4
            || check_ret == 5) {
            print_error(check_ret, i, count_err);
            i--;
            count_err++;
            continue;
        }
    }

    print_circle(c, i);

    fclose(file);
    free(c);
    c = NULL;

    return 0;
}