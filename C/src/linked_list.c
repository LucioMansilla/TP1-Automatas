#include "../libs/linked_list.h"
#include <stdio.h>
#include <stdlib.h>

List_List *create_empty_list_list()
{
  List_List *list = (List_List *)malloc(sizeof(List_List));
  list->next = NULL;
  list->size = 0;
  return list;
}


void print_list_list(List_List *list)
{
  int size = list->size;
  List_List* curr = list->next;
   for (int i = 0; i < size; i++)
  {
    print_list(curr->list);
    curr = curr->next;
  }  
}


int contains_any(List *l1, List *l2)
{
  for (int i = 0; i < l1->size; i++)
  {
    if (contains(l2, get_data(l1, i)))
    {
      return 1;
    }
  }
  return 0;
}


int equals(List *l1, List *l2) {
  if (l1->size != l2->size) {
    return 0;
  }

  for (int i = 0; i < l1->size; i++) {
    if (!contains(l2, get_data(l1, i))) {
      return 0;
    }
  }

  return 1;
}

int get_idx(List *ls, int data) {
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

Node *create_node(int data) {
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
  Node *new_node = create_node(data);
  new_node->next = ls->next;
  ls->next = new_node;
  ls->size++;
}

void add_list_list(List_List *ls, List *data) {
  
  if(ls->next == NULL){
    ls->next = (List_List *)malloc(sizeof(List_List));
    ls->next->list = data;
    ls->next->next = NULL;
    ls->size = 1;
    return;
  }
  List_List *cur = ls->next;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  List_List *new_node = (List_List *)malloc(sizeof(List_List));
  new_node->list = data;
  new_node->next = NULL;
  cur->next = new_node;
  ls->size++;

}

List_List* create_node_list_list(List_List *ls, List *data) {
  List_List *new_node = (List_List *)malloc(sizeof(List_List));
  new_node->list = data;
  new_node->next = NULL;
  ls->next = new_node;
  return new_node;
}


void append(List *ls, int data) {
  Node *cur = ls->next;
  if (!contains(ls, data)) {
    if (cur == NULL) {
      Node *new_node = create_node(data);
      ls->next = new_node;
      ls->size++;
      return;
    }

    while (cur->next != NULL) {
      cur = cur->next;
    }
    Node *new_node = create_node(data);
    cur->next = new_node;
    ls->size++;
  }
}

List *create_empty_list() {
  List *ls = (List *)malloc(sizeof(List));
  ls->next = NULL;
  ls->size = 0;
  return ls;
}

void print_list(List *ls) {
 
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

List *create_from(int array[], int length) {

  List *ls = create_empty_list();
  for (int i = 0; i < length; i++) {
    add(ls, array[i]);
  }
  return ls;
}

int get_data(List *l, int idx) {
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

List *create_K(int size_k) {
  List *list = create_empty_list();
  for (int i = 0; i < size_k; i++) {
    add(list, i);
  }
  return list;
}

void free_list(List *ls) {
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

