#include "../libs/linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int equals(List *l1, List *l2) {
  if (l1->size != l2->size) {
    return 0;
  }

  for (int i = 0; i < l1->size; i++) {
    if (!contains(l2, getData(l1, i))) {
      return 0;
    }
  }

  return 1;
}

int getIdx(List *ls, int data) {
  Node *cur = ls->next;
  int idx = 0;
  while (cur != NULL) {
    if (cur->data == data) {
      return idx;
    }
    cur = cur->next;
    idx++;
  }
  return -1;
}

Node *createNode(int data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  return node;
}

int contains(List *ls, int data) {
  Node *cur = ls->next;
  while (cur != NULL) {
    if (cur->data == data) {
      return 1;
    }
    cur = cur->next;
  }
  return 0;
}

void add(List *ls, int data) {
  Node *cur = ls->next;
  while (cur != NULL) {
    if (cur->data == data) {
      return;
    }
    cur = cur->next;
  }
  Node *newNode = createNode(data);
  newNode->next = ls->next;
  ls->next = newNode;
  ls->size++;
}

void append(List *ls, int data) {
  Node *cur = ls->next;
  if (!contains(ls, data)) {
    if (cur == NULL) {
      Node *newNode = createNode(data);
      ls->next = newNode;
      ls->size++;
      return;
    }

    while (cur->next != NULL) {
      cur = cur->next;
    }
    Node *newNode = createNode(data);
    cur->next = newNode;
    ls->size++;
  }
}

List *createEmptyList() {
  List *ls = (List *)malloc(sizeof(List));
  ls->next = NULL;
  ls->size = 0;
  return ls;
}

void printList(List *ls) {
  Node *cur = ls->next;
  if (cur == NULL) {
    printf("Empty list\n");
    return;
  }

  while (cur != NULL) {
    printf("%d", cur->data);
    cur = cur->next;
    if (cur != NULL) {
      printf("->");
    }
  }
  printf("->NULL\n");
}

List *createFrom(int array[], int length) {

  List *ls = createEmptyList();
  for (int i = 0; i < length; i++) {
    add(ls, array[i]);
  }
  return ls;
}

int getData(List *l, int idx) {
  int i = 0;
  Node *current = l->next;
  while (i < idx) {
    current = current->next;
    i++;
  }
  if (current == NULL) {
    return -1;
  }
  return current->data;
}

List *createK(int sizeK) {
  List *list = createEmptyList();
  for (int i = 0; i < sizeK; i++) {
    add(list, i);
  }
  return list;
}

void freeList(List *ls) {
  if (ls == NULL) {
    printf("Error: Cannot free null list\n");
    return;
  }
  Node *cur = ls->next;
  while (cur != NULL) {
    Node *aux = cur;
    cur = cur->next;
    free(aux);
  }
  free(ls);
}
