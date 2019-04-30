#define MAX 100

typedef struct {
    double x;
    double y;
    double r;
    int index;
} Circle;

void print_circle(Circle* c, int w0);
int run(char* str, Circle* c);
