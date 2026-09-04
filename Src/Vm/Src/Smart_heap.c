#pragma once
#include "Calc.c"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// SMART HEAP
//
// Reemplaza al antiguo sistema de stack (lista enlazada Deque) por un
// arreglo dinámico contiguo.
//
// Responsabilidades separadas:
//   write / read : leen y modifican VALORES por índice.
//   reserve      : cambia el TAMAÑO del heap (capacity).
//
// IMPORTANTE: `amount` es SOLO un contador de slots ocupados. Nunca debe
// usarse como índice para añadir valores (podría sobrescribir datos). El
// índice de escritura/lectura lo decide el llamador (la VM). Cada slot del
// arreglo debe poder leerse de forma segura: los slots no ocupados quedan
// en cero (slots vacíos).
// ==========================================

typedef struct {
  size_t amount;    // contador de slots ocupados (NO se usa como índice)
  size_t capacity;  // tamaño del buffer (slots reservados)
  PaxoVar *data_array;
} Smart_heap;

// Initialization
static inline Smart_heap create_heap(size_t initial_capacity) {
  Smart_heap heap;
  heap.amount = 0;
  heap.capacity = initial_capacity;

  if (initial_capacity > 0) {
    heap.data_array = calloc(initial_capacity, sizeof(PaxoVar));
  } else {
    heap.data_array = NULL;
  }

  return heap;
}

// Cleanup to prevent memory leaks
void free_heap(Smart_heap *heap) {
  if (heap == NULL)
    return;
  free(heap->data_array);
  heap->data_array = NULL;
  heap->amount = 0;
  heap->capacity = 0;
}

// Los "otros": cambian el tamaño del heap. Garantiza que exista capacidad
// para al menos `need_capacity` slots, creciendo (o reservando) el buffer
// si es necesario. Los nuevos slots quedan en cero para poder leerse.
bool heap_reserve(Smart_heap *heap, size_t need_capacity) {
  if (heap == NULL)
    return false;

  if (need_capacity <= heap->capacity)
    return true;

  size_t new_capacity = (heap->capacity == 0) ? 8 : heap->capacity;
  while (new_capacity < need_capacity)
    new_capacity *= 2;

  PaxoVar *temp = realloc(heap->data_array, new_capacity * sizeof(PaxoVar));
  if (temp == NULL)
    return false;

  // Los nuevos slots (de old_capacity a new_capacity) quedan en cero.
  memset(temp + heap->capacity, 0,
         (new_capacity - heap->capacity) * sizeof(PaxoVar));

  heap->data_array = temp;
  heap->capacity = new_capacity;
  return true;
}

// "write": escribe `var` en el slot `index` (modifica el valor).
// actualiza `amount` solo como contador de slots ocupados; no se usa aquí
// como índice de escritura.
bool heap_write(Smart_heap *heap, size_t index, PaxoVar var) {
  if (heap == NULL || heap->data_array == NULL || index >= heap->capacity)
    return false;

  heap->data_array[index] = var;

  if (index + 1 > heap->amount)
    heap->amount = index + 1;

  return true;
}

// "read": devuelve un puntero al valor en `index`. Si el heap no está
// inicializado o el slot no fue reservado, devuelve NULL.
PaxoVar *heap_read(Smart_heap *heap, size_t index) {
  if (heap == NULL || heap->data_array == NULL || index >= heap->capacity)
    return NULL;
  return &heap->data_array[index];
}
