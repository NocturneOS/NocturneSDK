#include <stddef.h>
#include <stdlib.h>

/*
 * Comparison-based sort on raw memory.
 *
 * Strategy: quicksort with a median-of-three pivot and Lomuto partitioning.
 * Partitions of size <= INSERTION_SORT_THRESHOLD are finished with insertion
 * sort, which is faster and avoids deep recursion on nearly sorted input.
 * Recursion is only performed on the smaller partition and the larger one is
 * handled by a loop, so stack depth is O(log n) even in the worst case.
 */

#define INSERTION_SORT_THRESHOLD 16

static void swap_bytes(char *a, char *b, size_t size) {
  size_t i;

  for (i = 0; i < size; i++) {
    char tmp = a[i];
    a[i] = b[i];
    b[i] = tmp;
  }
}

static void insertion_sort(char *base, size_t nmemb, size_t size,
                           int (*compar)(const void *, const void *)) {
  size_t i;

  for (i = 1; i < nmemb; i++) {
    size_t j = i;

    while (j > 0 &&
           compar(base + (j - 1) * size, base + j * size) > 0) {
      swap_bytes(base + (j - 1) * size, base + j * size, size);
      j--;
    }
  }
}

static void qsort_range(char *base, size_t nmemb, size_t size,
                        int (*compar)(const void *, const void *)) {
  while (nmemb > INSERTION_SORT_THRESHOLD) {
    char *low = base;
    char *high = base + (nmemb - 1) * size;
    char *middle = base + (nmemb / 2) * size;
    char *pivot;
    char *store;
    char *p;
    size_t left_count;
    size_t right_count;

    /* Order low / middle / high so that "middle" holds the median. */
    if (compar(low, middle) > 0) {
      swap_bytes(low, middle, size);
    }
    if (compar(low, high) > 0) {
      swap_bytes(low, high, size);
    }
    if (compar(middle, high) > 0) {
      swap_bytes(middle, high, size);
    }

    /* Move the pivot to the end and partition everything before it. */
    swap_bytes(middle, high, size);
    pivot = high;
    store = low;

    for (p = low; p < high; p += size) {
      if (compar(p, pivot) < 0) {
        swap_bytes(store, p, size);
        store += size;
      }
    }

    swap_bytes(store, high, size);

    left_count = (size_t)(store - low) / size;
    right_count = nmemb - left_count - 1;

    /* Recurse into the smaller half, loop over the larger one. */
    if (left_count < right_count) {
      qsort_range(low, left_count, size, compar);
      base = store + size;
      nmemb = right_count;
    } else {
      qsort_range(store + size, right_count, size, compar);
      base = low;
      nmemb = left_count;
    }
  }

  insertion_sort(base, nmemb, size, compar);
}

void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *)) {
  if (nmemb < 2 || size == 0) {
    return;
  }

  qsort_range((char *)base, nmemb, size, compar);
}
