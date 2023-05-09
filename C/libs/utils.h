#ifndef UTILS_H
#define UTILS_H
#include "transition.h"

#define ALPHABET_SIZE 123
#define SENTINEL -1
#define LAMBDA 47

List **getDelta(Transition transitions[], int k);
int isVisited(int visited[][2], int state, int symbol, int size);
int ord(char c);
char chr(int i);
int in(List *list, List **listArray, int listArraySize);

#endif