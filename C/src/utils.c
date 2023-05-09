#include "../libs/utils.h"
#include <stdio.h>
#include <stdlib.h>

List **getDelta(Transition transitions[], int k) {
  int kLength = k;
  List **matrixList = (List **)malloc(kLength * sizeof(List *));

  for (int i = 0; i < kLength; i++) {
    matrixList[i] = (List *)malloc(ALPHABET_SIZE * sizeof(List));
    for (int j = 0; j < ALPHABET_SIZE; j++) {
      matrixList[i][j] = *createEmptyList();
    }
  }

  int i = 0;
  while (transitions[i].from != SENTINEL) {
    matrixList[transitions[i].from][transitions[i].symbol] = *transitions[i].to;
    i++;
  }

  return matrixList;
}

int isVisited(int visited[][2], int state, int symbol, int size) {
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
  return abs(48 - (int)c);
}

char chr(int i) {
  if (i == LAMBDA)
    return (char)95;
  return (char)(48 + i);
}

int in(List *list, List **listArray, int listArraySize) {
  for (int i = 0; i < listArraySize; i++) {
    if (equals(list, listArray[i])) {
      return i;
    }
  }
  return -1;
}
