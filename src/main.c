#include "circle.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int w0 = 1;
    FILE* file;
    file = fopen("coordinates.txt", "r");
    if (!file) {
        printf("Can`t open file\n");
        return -1;
    }
    char str[100];
    Circle* c = (Circle*)malloc(sizeof(*c));
    while (!feof(file)) {
        fgets(str, sizeof(str), file);
        if (run(str, c) == -1) {
            return -1;
        }
        print_circle(c, w0);
        w0++;
    }

    fclose(file);
    return 0;
}
