#include <stdio.h>

typedef elem int

typedef stuct node {
  elem info;
  node *next;
} Node;

typedef struct {
  Node *inf, *sup;
} Fila;
