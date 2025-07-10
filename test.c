#define GARRY_IMPLEMENTATION
#include "garry.h"
#include <stdio.h> // printf()

struct test {
    int a;
    int b;
};

#define RAND_10_TO_20() (rand() % 11 + 10)

int main(int argc, const char *argv[]) {
    struct test *arr = NULL; // can be any type or struct
    for (int i = 0; i < RAND_10_TO_20(); i++) {
        struct test t = {i, i*2};
	    garry_append(arr, t);
    }
    for (int i = 0; i < garry_count(arr); i++) {
        struct test t = arr[i];
        printf("%d: %d, %d\n", i, t.a, t.b);
    }
    garry_free(arr);
    return 0;
}
