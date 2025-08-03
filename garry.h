/* garry.h -- https://github.com/takeiteasy/garry

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
 SOFTWARE. */

// Based on stetchy_buffer.h by nothings https://github.com/nothings/stb/blob/master/deprecated/stretchy_buffer.h

#ifndef GARRY_HEADER
#define GARRY_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifndef GARRY_REALLOC
#define GARRY_REALLOC(...) realloc(__VA_ARGS__)
#endif

#ifndef GARRY_FREE
#define GARRY_FREE(...) free(__VA_ARGS__)
#endif

#define __garry_raw(a)              ((int *) (a) - 2)
#define __garry_m(a)                __garry_raw(a)[0]
#define __garry_n(a)                __garry_raw(a)[1]

#define __garry_needgrow(a,n)       ((a)==0 || __garry_n(a)+n >= __garry_m(a))
#define __garry_grow(a,n)           __garry_growf((void **) &(a), (n), sizeof(*(a)))
#define __garry_maybegrow(a,n)      (__garry_needgrow(a,(n)) ? __garry_grow(a,n) : 0)

#define __garry_needshrink(a)       (__garry_m(a) > 4 && __garry_n(a) <= __garry_m(a) / 4)
#define __garry_maybeshrink(a)      (__garry_needshrink(a) ? __garry_shrink(a) : 0)
#define __garry_shrink(a)           __garry_shrinkf((void **) &(a), sizeof(*(a)))

#define garry_free(a)               ((a) ? GARRY_FREE(__garry_raw(a)),0 : 0)
#define garry_append(a, v)          (__garry_maybegrow(a,1), (a)[__garry_n(a)++] = (v))
#define garry_count(a)              ((a) ? __garry_n(a) : 0)
#define garry_insert(a, idx, v)     (__garry_maybegrow(a,1), memmove(&a[idx+1], &a[idx], (__garry_n(a)++ - idx) * sizeof(*(a))), a[idx] = (v))
#define garry_push(a, v)            (garry_insert(a,0,v))
#define garry_cdr(a)                (void*)(garry_count(a) > 1 ? &(a+1) : NULL)
#define garry_car(a)                (void*)((a) ? &(a)[0] : NULL)
#define garry_last(a)               (void*)((a) ? &(a)[__garry_n(a)-1] : NULL)
#define garry_pop(a)                (--__garry_n(a), __garry_maybeshrink(a))
#define garry_remove_at(a, idx)     (idx == __garry_n(a)-1 ? memmove(&a[idx], &arr[idx+1], (--__garry_n(a) - idx) * sizeof(*(a))) : garry_pop(a), __garry_maybeshrink(a))
#define garry_shift(a)              (garry_remove_at(a, 0))
#define garry_clear(a)              ((a) ? (__garry_n(a) = 0) : 0, __garry_shrink(a))

void  __garry_growf(void **arr, int increment, int itemsize);
void  __garry_shrinkf(void **arr, int itemsize);

#ifdef __cplusplus
}
#endif
#endif // GARRY_HEADER

#ifdef GARRY_IMPLEMENTATION
void __garry_growf(void **arr, int increment, int itemsize) {
    int m = *arr ? 2 * __garry_m(*arr) + increment : increment + 1;
    void *p = (void*)GARRY_REALLOC(*arr ? __garry_raw(*arr) : 0, itemsize * m + sizeof(int) * 2);
    assert(p);
    if (p) {
        if (!*arr)
            ((int *)p)[1] = 0;
        *arr = (void*)((int*)p + 2);
        __garry_m(*arr) = m;
    }
}

void __garry_shrinkf(void **arr, int itemsize) {
    int m = *arr ? __garry_m(*arr) / 2 : 0;
    void *p = (void*)GARRY_REALLOC(*arr ? __garry_raw(*arr) : 0, itemsize * m + sizeof(int) * 2);
    assert(p);
    if (p) {
        *arr = (void*)((int*)p + 2);
        __garry_m(*arr) = m;
    }
}
#endif
