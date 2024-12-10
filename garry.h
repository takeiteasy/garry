#ifndef GARRY_HEADER
#define GARRY_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#define __garry_raw(a)           ((int *)(void *) (a) - 2)
#define __garry_m(a)             __garry_raw(a)[0]
#define __garry_n(a)             __garry_raw(a)[1]
#define __garry_needgrow(a,n)    ((a)==0 || __garry_n(a)+(n) >= __garry_m(a))
#define __garry_maybegrow(a,n)   (__garry_needgrow(a,(n)) ? __garry_grow(a,n) : 0)
#define __garry_grow(a,n)        (*((void **)&(a)) = __garry_growf((a), (n), sizeof(*(a))))
#define __garry_needshrink(a)    (__garry_m(a) > 4 && __garry_n(a) <= __garry_m(a) / 4)
#define __garry_maybeshrink(a)   (__garry_needshrink(a) ? __garry_shrink(a) : 0)
#define __garry_shrink(a)        (*((void **)&(a)) = __garry_shrinkf((a), sizeof(*(a))))

#define garry_free(a)           ((a) ? free(__garry_raw(a)),((a)=NULL) : 0)
#define garry_append(a,v)       (__garry_maybegrow(a,1), (a)[__garry_n(a)++] = (v))
#define garry_insert(a, idx, v) (__garry_maybegrow(a,1), memmove(&a[idx+1], &a[idx], (__garry_n(a)++ - index) * sizeof(*(a))), a[idx] = (v))
#define garry_push(a,v)         (garry_insert(a,0,v))
#define garry_count(a)          ((a) ? __garry_n(a) : 0)
#define garry_reserve(a,n)      (__garry_maybegrow(a,n), __garry_n(a)+=(n), &(a)[__garry_n(a)-(n)])
#define garry_begin(a)          ((a) ? (a)[0] : 0)
#define garry_end(a)            ((a) ? (a)[__garry_n(a)-1] : 0)
#define garry_pop(a)            (--__garry_n(a), __garry_maybeshrink(a))
#define garry_remove_at(a, idx) (idx == __garry_n(a)-1 ? memmove(&a[idx], &arr[idx+1], (--__garry_n(a) - index) * sizeof(*(a))) : garry_pop(a), __garry_maybeshrink(a))
#define garry_shift(a)          (garry_remove_at(a, 0))
#define garry_clear(a)          ((a) ? (__garry_n(a) = 0) : 0, __garry_shrink(a))

void *__garry_growf(void *arr, int increment, int itemsize);
void *__garry_shrinkf(void *arr, int itemsize);

#ifdef __cplusplus
}
#endif
#endif // GARRY_HEADER

#ifdef GARRY_IMPLEMENTATION
void *__garry_growf(void *arr, int increment, int itemsize) {
    int dbl_cur = arr ? 2 * __garry_m(arr) : 0;
    int min_needed = garry_count(arr) + increment;
    int m = dbl_cur > min_needed ? dbl_cur : min_needed;
    int *p = (int*)realloc(arr ? __garry_raw(arr) : 0, itemsize * m + sizeof(int) * 2);
    if (p) {
        if (!arr)
            p[1] = 0;
        p[0] = m;
        return p + 2;
    }
    return (void*)(2 * sizeof(int));
}

void *__garry_shrinkf(void *arr, int itemsize) {
    int new_capacity = __garry_m(arr) / 2;
    int *p = (int*)realloc(arr ? __garry_raw(arr) : 0, itemsize * new_capacity + sizeof(int) * 2);
    if (p) {
        p[0] = new_capacity;
        return p + 2;
    }
    return (void*)(2*sizeof(int));
}
#endif
