#ifndef UTILS_H
#define UTILS_H
#include "transition.h"

#define ALPHABET_SIZE 123
#define SENTINEL -1
#define LAMBDA 47
#define DELTA_SYMBOL 48

List **get_delta(Transition transitions[], int k);
int is_visited(int visited[][2], int state, int symbol, int size);
int ord(char c);
char chr(int i);
int in(List *list, List **list_array, int list_array_size);

#endif