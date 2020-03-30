#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 4

#define VECTOR_INIT(vec) VECTOR vec; vector_init(&vec)
#define VECTOR_ADD(vec, item) vector_add(&vec, (void *) item)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void *) item)
#define VECTOR_GET(vec, type, id) (type) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_TOTAL(vec) vector_total(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)

typedef struct VECTOR {
  void **items;
  int capacity;
  int total;
} VECTOR;

void vector_init(VECTOR *);
int vector_total(VECTOR *);
static void vector_resize(VECTOR *, int);
void vector_add(VECTOR *, void *);
void vector_set(VECTOR *, int, void *);
void *vector_get(VECTOR *, int);
void vector_delete(VECTOR *, int);
void vector_free(VECTOR *);

#endif
