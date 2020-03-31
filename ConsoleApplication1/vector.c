#pragma once

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void vector_init(VECTOR *v)
{
  v->capacity = VECTOR_INIT_CAPACITY;
  v->total = 0;
  v->items = malloc(sizeof(char *) * v->capacity);
}

int vector_total(VECTOR *v)
{
  return v->total;
}

static void vector_resize(VECTOR *v, int capacity)
{
#ifdef DEBUG_ON
  printf("vector_resize: %d to %d\n", v->capacity, capacity);
#endif

  void **items = realloc(v->items, sizeof(char *) * capacity);
  if (items) {
    v->items = items;
    v->capacity = capacity;
  }
}

void vector_add(VECTOR *v, void *item)
{
  if (v->capacity == v->total)
    vector_resize(v, v->capacity * 2);
  v->items[v->total++] = item;
}

void vector_set(VECTOR *v, int index, void *item)
{
  if (index >= 0 && index < v->total)
    v->items[index] = item;
}

void vector_print(VECTOR *v)
{
  int i = 0;
  for (; i < v->total; i++)
  {
    printf("%i, ", v->items[i]);
  };
}

void *vector_get(VECTOR *v, int index)
{
  if (index >= 0 && index < v->total)
    return v->items[index];
  return NULL;
}

void vector_delete(VECTOR *v, int index)
{
  if (index < 0 || index >= v->total)
    return;

  v->items[index] = NULL;

  for (int i = index; i < v->total - 1; i++) {
    v->items[i] = v->items[i + 1];
    v->items[i + 1] = NULL;
  }

  v->total--;

  if (v->total > 0 && v->total == v->capacity / 4)
    vector_resize(v, v->capacity / 2);
}

void vector_free(VECTOR *v)
{
  free(v->items);
}