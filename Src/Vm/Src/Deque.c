// Deque.h o la sección de estructuras de Deque.c
#pragma once
#include "Calc.c" // Para tener acceso a PaxoVar
#include <stdlib.h>

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

// Funciones básicas adaptadas
void deque_push_back(Deque *dq, PaxoVar var) {
  Node *nuevo = (Node *)malloc(sizeof(Node));
  nuevo->data = var;
  nuevo->next = NULL;
  nuevo->prev = dq->tail;

  if (dq->tail)
    dq->tail->next = nuevo;
  else
    dq->head = nuevo;

  dq->tail = nuevo;
  dq->size++;
}

PaxoVar deque_pop_back(Deque *dq) {
  if (!dq->tail)
    return (PaxoVar){0}; // Manejo de vacío
  Node *temp = dq->tail;
  PaxoVar val = temp->data;

  dq->tail = dq->tail->prev;
  if (dq->tail)
    dq->tail->next = NULL;
  else
    dq->head = NULL;

  free(temp);
  dq->size--;
  return val;
}
