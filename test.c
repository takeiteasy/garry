#define GARRY_IMPLEMENTATION
#include "garry.h"
#include <stdio.h> // printf()
#include <stdlib.h> // rand()

#define RAND_10_TO_20() (rand() % 11 + 10)

int main(int argc, const char *argv[]) {
    int *arr = NULL; // can be any type or struct
    for (int i = 0; i < RAND_10_TO_20(); i++)
	garry_append(arr, i);
    for (int i = 0; i < garry_count(arr); i++)
        printf("%d: %d\n", i, arr[i]);
    garry_free(arr);
    return 0;
}
