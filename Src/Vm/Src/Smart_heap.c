#pragma once
#include "Calc.c"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  size_t amount;
  size_t capacity;
  PaxoVar *data_array;
} Smart_heap;

// Initialization
static inline Smart_heap create_heap(size_t initial_capacity) {
  Smart_heap heap;
  heap.amount = 0;
  heap.capacity = initial_capacity;

  // Allocate initial memory block
  if (initial_capacity > 0) {
    heap.data_array = malloc(initial_capacity * sizeof(PaxoVar));
  } else {
    heap.data_array = NULL;
  }

  return heap;
}

// Cleanup to prevent memory leaks
void free_heap(Smart_heap *heap) {
  if (heap->data_array != NULL) {
    free(heap->data_array);
    heap->data_array = NULL;
  }
  heap->amount = 0;
  heap->capacity = 0;
}

bool heap_push(Smart_heap *heap, PaxoVar new_element) {
  if (heap == NULL)
    return false;

  /* Si el arreglo está lleno, duplicar su capacidad */
  if (heap->amount >= heap->capacity) {
    // Si la capacidad es 0, iniciamos con 8 espacios. Si no, duplicamos.
    size_t new_capacity = (heap->capacity == 0) ? 8 : heap->capacity * 2;

    // Usar un puntero temporal para evitar perder datos si realloc falla
    PaxoVar *temp_array =
        realloc(heap->data_array, new_capacity * sizeof(PaxoVar));

    if (temp_array == NULL) {
      return false; /* Error: No hay memoria suficiente */
    }

    heap->data_array = temp_array;
    heap->capacity = new_capacity;
  }

  /* Insertar el nuevo elemento y aumentar la longitud */
  heap->data_array[heap->capacity - 1] = new_element;
  heap->amount++;

  return true;
}

bool heap_pop(Smart_heap *heap) {
  if (heap == NULL)
    return false;
  size_t new_capacity = (heap->capacity == 0) ? 8 : heap->capacity / 2;
  PaxoVar *temp_array =
      realloc(heap->data_array, new_capacity * sizeof(PaxoVar));
  if (temp_array == NULL) {
    return false; /* Error: No hay memoria suficiente */
  }

  heap->data_array = temp_array;
  heap->capacity = new_capacity;
}

PaxoVar *heap_read(Smart_heap *heap, size_t index) {
  if (heap == NULL || index >= heap->capacity || heap->data_array == NULL) {
    return NULL; /* Out of bounds or uninitialized heap */
  }
  return &heap->data_array[index];
}

bool heap_write(Smart_heap *heap, size_t index, PaxoVar var) {
  if (heap == NULL || index >= heap->capacity) {
    return false; /* Out of bounds or uninitialized heap */
  }

  PaxoVar old_value = heap->data_array[index];

  /* Ajustar amount solo si el estado real del slot cambia entre NULL y valor */
  if (old_value == NULL && var != NULL) {
    heap->amount++;
  } else if (old_value != NULL && var == NULL) {
    if (heap->amount > 0)
      heap->amount--;
  }
  heap->data_array[index] = var;
  return true;
}
