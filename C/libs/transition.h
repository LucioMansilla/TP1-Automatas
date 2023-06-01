#ifndef TRANSITION_H
#define TRANSITION_H
#include "linked_list.h"

typedef struct {
  int from;
  int symbol;
  List *to;
} Transition;

Transition createTransition(int from, int symbol, List *to);
void printTransition(Transition t);
#endif