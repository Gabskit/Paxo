#pragma once
#include "Calc.c"
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
  PaxoVar data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  size_t size;
} Deque;

// Inicializa una instancia de Deque limpia
static inline Deque *deque_create(void) {
  Deque *dq = (Deque *)malloc(sizeof(Deque));
  if (!dq) return NULL;
  dq->head = NULL;
  dq->tail = NULL;
  dq->size = 0;
  return dq;
}

// Inserción al final (LIFO - Operación Push de la VM)
bool deque_push_back(Deque *dq, PaxoVar var) {
  if (!dq) return false;
  Node *nuevo = (Node *)malloc(sizeof(Node));
  if (!nuevo) return false;

  nuevo->data = var;
  nuevo->next = NULL;
  nuevo->prev = dq->tail;

  if (dq->tail)
    dq->tail->next = nuevo;
  else
    dq->head = nuevo;

  dq->tail = nuevo;
  dq->size++;
  return true;
}

// Extracción del final (LIFO - Operación Pop de la VM)
PaxoVar deque_pop_back(Deque *dq) {
  if (!dq || !dq->tail) return (PaxoVar){0};

  Node *temp = dq->tail;
  PaxoVar val = temp->data;

  dq->tail = temp->prev;
  if (dq->tail)
    dq->tail->next = NULL;
  else
    dq->head = NULL;

  free(temp);
  dq->size--;
  return val;
}

// Inspección del elemento superior sin extraerlo
PaxoVar deque_peek_back(const Deque *dq) {
  if (!dq || !dq->tail) return (PaxoVar){0};
  return dq->tail->data;
}

// Inserción al inicio (Útil para colar operaciones prioritarias)
bool deque_push_front(Deque *dq, PaxoVar var) {
  if (!dq) return false;
  Node *nuevo = (Node *)malloc(sizeof(Node));
  if (!nuevo) return false;

  nuevo->data = var;
  nuevo->prev = NULL;
  nuevo->next = dq->head;

  if (dq->head)
    dq->head->prev = nuevo;
  else
    dq->tail = nuevo;

  dq->head = nuevo;
  dq->size++;
  return true;
}

// Extracción del inicio
PaxoVar deque_pop_front(Deque *dq) {
  if (!dq || !dq->head) return (PaxoVar){0};

  Node *temp = dq->head;
  PaxoVar val = temp->data;

  dq->head = temp->next;
  if (dq->head)
    dq->head->prev = NULL;
  else
    dq->tail = NULL;

  free(temp);
  dq->size--;
  return val;
}

// Liberación total de memoria al detener la VM
void deque_free(Deque *dq) {
  if (!dq) return;
  Node *actual = dq->head;
  while (actual) {
    Node *siguiente = actual->next;
    free(actual);
    actual = siguiente;
  }
  free(dq);
}

// Retorna el tamaño actual del deque
static inline size_t deque_size(const Deque *dq) {
  return dq ? dq->size : 0;
}
