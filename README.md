# garry.h

A **G**eneric dynamic **ARR**a**Y** for C -- fork from [stb/deprecated/stretchy_buffer.h](https://github.com/nothings/stb/blob/master/deprecated/stretchy_buffer.h).

```c
#define GARRY_IMPLEMENTATION
#include "garry.h"
#include <stdio.h> // printf()
#include <stdlib.h> // rand()

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
``` 

## LICENSE

```
MIT License

Copyright (c) 2024 George Watson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
