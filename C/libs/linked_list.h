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

typedef struct _list_list {
  List *list;
  struct _list_list *next;
  int size;
} List_List;


int contains_any(List *l1, List *l2);
List *create_from(int array[], int length);
List *create_empty_list();
int equals(List *l1, List *l2);
int get_idx(List *list, int data);
int contains(List *list, int data);
void add(List *list, int data);
void print_list(List *list);
int get_data(List *list, int idx);
void append(List *ls, int data);
List *create_K(int size_k);
void free_list(List *list);
void add_list_list(List_List *ls, List *data);
void print_list_list(List_List *list);
List_List *create_empty_list_list();


#endif
