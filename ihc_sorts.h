/*
 * ihc_sorts.h - v0.1 - ilonic23 2026
 * This is a single-header-file implementing a variety of sorting algorithms.
 * To use, #define this *once* in a source file: IHC_SORTS_IMPLEMENTATION
 * Then #include "ihc_sorts.h"
 * You should also #define IHC_SORTS_TYPE to set the type that you use when sorting.
 *
 * TABLE OF CONTENTS:
 * Table of contents - line 8
 * Compile-time options - line 13
 * Documentation - line 32
 * Credits - line 49
 *
 * COMPILE-TIME OPTIONS:
 *
 * #define IHC_SORTS_TYPE         - the type of arrays that should be used in sorts.
 *                                  Without it's being defined you will get an error.
 * #define IHCSORT_NO_SHORT_NAMES - By default the names of the functions ( macros) are named without
 *                                  a prefix, defining this will add the prefix 'ihc_'
 * #define ihc_lt(a,b)            - the less than macro that checks if a is less than b.
 *                                  It is already defined, but if you want to compare
 *                                  more complex structures, change it.
 * #define ihc_lte(a,b)           - the less/equal macro that checks if a is less or equal to b.
 *                                  It is already defined, but if you want to compare
 *                                  more complex structures, change it.
 * #define ihc_gt(a,b)            - the greater than than macro that checks if a is greater than b.
 *                                  It is already defined, but if you want to compare
 *                                  more complex structures, change it.
 * #define ihc_gte(a,b)           - the greater/equal macro that checks if a is greater or equal to b.
 *                                  It is already defined, but if you want to compare
 *                                  more complex structures, change it.
 * DOCUMENTATION:
 * There are multiple sorting variants implemented:
 * bubble_sort
 * selection_sort
 * insertion_sort
 * quick_sort
 * heap_sort
 * intro_sort
 * Each function takes two parameters:
 * IHC_SORTS_TYPE *arr - pointer to an array
 * size_t len - length of the array
 *
 * If you want to sort only a subarray, you can provide ihc_subarray to a sorting function.
 * For examle:
 * quick_sort(ihc_subarray(arr, 3, 10));
 * This will give the function an array starting from index 3, and ending with index 10 (exclusive) * 
 *
 * CREDITS:
 * ilonic23 - library
*/

#ifndef IHC_SORTS_H
#define IHC_SORTS_H

#ifndef IHC_SORTS_TYPE
#error "'IHC_SORTS_TYPE' must be defined"
#endif // IHC_SORTS_TYPE

#include "stddef.h"

#ifndef IHCSORT_NO_SHORT_NAMES
#define bubble_sort     ihc_bubble_sort
#define selection_sort  ihc_selection_sort
#define insertion_sort  ihc_insertion_sort
#define quick_sort      ihc_quick_sort
#define heap_sort       ihc_heap_sort
#define intro_sort      ihc_intro_sort
#endif // IHCSORT_NO_SHORT_NAMES

void ihc_bubble_sort        (IHC_SORTS_TYPE *arr, size_t len);
void ihc_selection_sort     (IHC_SORTS_TYPE *arr, size_t len);
void ihc_insertion_sort     (IHC_SORTS_TYPE *arr, size_t len);
void ihc_quick_sort         (IHC_SORTS_TYPE *arr, size_t len);
void ihc_heap_sort          (IHC_SORTS_TYPE *arr, size_t len);
void ihc_intro_sort         (IHC_SORTS_TYPE *arr, size_t len);

#ifdef IHC_SORTS_IMPLEMENTATION

#ifndef ihc_lt
#define ihc_lt(a, b) ((a) < (b))
#endif // ihc_lt

#ifndef ihc_lte
#define ihc_lte(a,b) ((a) <= (b))
#endif // ihc_lte

#ifndef ihc_gt
#define ihc_gt(a,b) ((a) > (b))
#endif // ihc_gt

#ifndef ihc_gte
#define ihc_gte(a,b) ((a) >= (b))
#endif // ihc_gte

#define ihc_subarray(a, s, e) (a+s), e-s

static void swap(IHC_SORTS_TYPE *a, IHC_SORTS_TYPE *b) {
    IHC_SORTS_TYPE temp = *a;
    *a = *b;
    *b = temp;
}

void ihc_bubble_sort(IHC_SORTS_TYPE *arr, size_t len) {
    size_t i;
    char swapped = 1;
    while (swapped) {
        swapped = 0;
        for (i = 0; i < len; i++) {
            if (ihc_gt(arr[i], arr[i + 1])) {
                swap(&arr[i], &arr[i+1]);
                swapped = 1;
            }
        }
    }
}

void ihc_selection_sort(IHC_SORTS_TYPE *arr, size_t len) {
    size_t i, j, min_idx;
    for (i = 0; i + 1 < len; i++) {
        min_idx = i;
        for (j = i + 1; j < len; j++)
            if (ihc_lt(arr[j], arr[min_idx]))
            min_idx = j;

        swap(&arr[i], &arr[min_idx]);
    }
}

void ihc_insertion_sort(IHC_SORTS_TYPE *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        IHC_SORTS_TYPE key = arr[i];
        size_t j = i;

        while (j > 0 && ihc_gt(arr[j - 1], key)) {
            arr[j] = arr[j - 1];
            j--;
        }

        arr[j] = key;
    }
}

static size_t partition(IHC_SORTS_TYPE *arr, size_t min, size_t max) {
    IHC_SORTS_TYPE pivot = arr[max];
    
    size_t i = min;

    for (size_t j = min; j < max; j++) {  // Changed: start at min, go until max-1
        if (ihc_lt(arr[j], pivot)) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[max]);
    return i;
}

static void quick_sort_inner(IHC_SORTS_TYPE *arr, size_t min, size_t max) {
    if (min < max) {
        size_t pi = partition(arr, min, max);

        if (pi > 0) {  // Guard against underflow
            quick_sort_inner(arr, min, pi - 1);
        }
        quick_sort_inner(arr, pi + 1, max);
    }
}

void ihc_quick_sort(IHC_SORTS_TYPE *arr, size_t len) {
    quick_sort_inner(arr, 0, len);
}

static void heapify(IHC_SORTS_TYPE *arr, size_t len, size_t i) {
    size_t largest = i;

    size_t l = 2*i+1, r = 2*i+2;

    if (l < len && ihc_gt(arr[l], arr[largest]))
        largest = l;
    if (r < len && ihc_gt(arr[r], arr[largest]))
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, len, largest);
    }
}

void ihc_heap_sort(IHC_SORTS_TYPE *arr, size_t len) {
    ptrdiff_t i;

    for (i = len/2 - 1; i >= 0; i--)
        heapify(arr, len, i);

    for (i = len - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Used for introsort internally in the header
// to calculate the max depth
static inline int floor_log2(size_t n)
{
    int r = 0;
    while (n >>= 1) r++;
    return r;
}

static IHC_SORTS_TYPE *median_of_three(IHC_SORTS_TYPE *a, IHC_SORTS_TYPE *b, IHC_SORTS_TYPE *c) {
    if (ihc_lt(*a, *b)) {
        if (ihc_lt(*b, *c)) return b;
        return ihc_lt(*a, *c) ? c : a;
    } else {
        if (ihc_lt(*a, *c)) return a;
        return ihc_lt(*b, *c) ? c : b;
    }
}

static IHC_SORTS_TYPE *intro_sort_partition(IHC_SORTS_TYPE *begin, IHC_SORTS_TYPE *end) {
    IHC_SORTS_TYPE *pivot = end - 1;
    IHC_SORTS_TYPE *i = begin;

    for (IHC_SORTS_TYPE *j = begin; j < pivot; j++) {
        if (ihc_lt(*j, *pivot)) {
            swap(i, j);
            i++;
        }
    }

    swap(i, pivot);
    return i;
}

static void intro_sort_util(IHC_SORTS_TYPE *begin, IHC_SORTS_TYPE *end, int max_depth) {
    size_t size = (size_t)(end - begin);

    if (size < 16) {
        ihc_insertion_sort(begin, size);
        return;
    }

    if (max_depth == 0) {
        ihc_heap_sort(begin, size);
        return;
    }

    IHC_SORTS_TYPE *mid = begin + size / 2;
    IHC_SORTS_TYPE *pivot = median_of_three(begin, mid, end - 1);
    swap(pivot, end - 1);

    IHC_SORTS_TYPE *p = intro_sort_partition(begin, end);

    intro_sort_util(begin, p, max_depth - 1);
    intro_sort_util(p + 1, end, max_depth - 1);
}

static void intro_sort_inner(IHC_SORTS_TYPE *arr, size_t min, size_t max) {
    size_t n = max - min;
    if (n < 2) return;
    int max_depth = 2 * floor_log2(n > 0 ? n : 1);
    intro_sort_util(arr + min, arr + max, max_depth);
}

void ihc_intro_sort(IHC_SORTS_TYPE *arr, size_t len) {
    intro_sort_inner(arr, 0, len);
}

#endif // IHC_SORTS_IMPLEMENTATION

#endif // IHC_SORTS_H
