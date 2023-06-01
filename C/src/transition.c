#include <stdio.h>
#include "../libs/utils.h"

Transition createTransition(int from, int symbol, List *to) {
  Transition t;
  t.from = from;
  t.symbol = symbol;
  t.to = to;
  return t;
}

void printTransition(Transition t)
{
  printf("From %d with %c to: ", t.from, (char)(t.symbol + DELTA_SYMBOL));
  printList(t.to);
}