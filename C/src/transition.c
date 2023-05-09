#include "../libs/transition.h"

Transition createTransition(int from, int symbol, List *to) {
  Transition t;
  t.from = from;
  t.symbol = symbol;
  t.to = to;
  return t;
}