#ifndef TRANSITION_H
#define TRANSITION_H
#include "linked_list.h"

typedef struct {
  int from;
  int symbol;
  List *to;
} Transition;

Transition create_transition(int from, int symbol, List *to);
void print_transition(Transition t);
#endif