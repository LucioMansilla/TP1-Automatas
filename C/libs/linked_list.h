#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct _list {
  Node *next;
  int size;
} List;

List *createFrom(int array[], int length);
List *createEmptyList();
int equals(List *l1, List *l2);
int getIdx(List *list, int data);
int contains(List *list, int data);
void add(List *list, int data);
Node *createNode(int data);
void printList(List *list);
int getData(List *list, int idx);
void append(List *ls, int data);
List *createK(int sizeK);
void freeList(List *list);

#endif
