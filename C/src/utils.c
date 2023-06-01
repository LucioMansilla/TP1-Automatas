#include "../libs/utils.h"
#include <stdio.h>
#include <stdlib.h>

List **get_delta(Transition transitions[], int k) {
  int k_length = k;
  List **matrix_list = (List **)malloc(k_length * sizeof(List *));

  for (int i = 0; i <k_length; i++) {
    matrix_list[i] = (List *)malloc(ALPHABET_SIZE  * sizeof(List));
    for (int j = 0; j < ALPHABET_SIZE; j++) {
      matrix_list[i][j] = *create_empty_list();
    }
  }

  int i = 0;
  while (transitions[i].from != SENTINEL) {
    matrix_list[transitions[i].from][transitions[i].symbol] = *transitions[i].to;
    i++;
  }

  return matrix_list;
}

int is_visited(int visited[][2], int state, int symbol, int size) {
  int i = 0;

  for (i = 0; i < size; i++) {
    if (visited[i][0] == state && visited[i][1] == symbol) {
      return 1;
    }
  }
  return 0;
}

int ord(char c) {
  if (c == '_')
    return LAMBDA;
  return abs(DELTA_SYMBOL - (int)c);
}

char chr(int i) {
  if (i == LAMBDA)
    return (char)95;
  return (char)(DELTA_SYMBOL + i);
}

int in(List *list, List **list_array, int list_array_size) {
  for (int i = 0; i < list_array_size; i++) {
    if (equals(list, list_array[i])) {
      return i;
    }
  }
  return -1;
}
