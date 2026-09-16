#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Calc.c"

typedef struct {
  int amount;
  size_t capacity;
  LEPVar *data_array;
} Smart_heap;

Smart_heap create_heap(size_t initial_capacity) {
    if (initial_capacity == 0) {
        return (Smart_heap){.amount = 0, .capacity = 0, .data_array = NULL};
    }
    LEPVar *slice = malloc(sizeof(LEPVar) * initial_capacity);
    if (!slice) return (Smart_heap){0, 0, NULL};
    memset(slice, 0, sizeof(LEPVar) * initial_capacity);
    return (Smart_heap){.amount = 0, .capacity = initial_capacity, .data_array = slice};
}

void free_heap(Smart_heap *heap) {
    if (heap && heap->data_array) {
        free(heap->data_array);
        heap->data_array = NULL;
    }
    if (heap) {
        heap->amount = 0;
        heap->capacity = 0;
    }
}

bool heap_reserve(Smart_heap *heap, size_t need_capacity) {
    if (!heap) return false;
    if (need_capacity <= heap->capacity) return true;

    size_t new_capacity = (heap->capacity == 0) ? 8 : heap->capacity;
    while (new_capacity < need_capacity) {
        new_capacity *= 2;
    }

    LEPVar *new_slice = realloc(heap->data_array, sizeof(LEPVar) * new_capacity);
    if (!new_slice) return false;

    memset(new_slice + heap->capacity, 0, sizeof(LEPVar) * (new_capacity - heap->capacity));
    heap->data_array = new_slice;
    heap->capacity = new_capacity;
    return true;
}

bool heap_write(Smart_heap *heap, size_t index, LEPVar var_val) {
    if (!heap || index >= heap->capacity) return false;
    heap->data_array[index] = var_val;
    int next_slot = (int)(index + 1);
    if (next_slot > heap->amount) {
        heap->amount = next_slot;
    }
    return true;
}

LEPVar *heap_read(Smart_heap *heap, size_t index) {
    if (!heap || index >= heap->capacity || !heap->data_array) return NULL;
    return &heap->data_array[index];
}
